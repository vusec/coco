#!/usr/bin/env python3

import subprocess as sp
import os
import argparse
import tempfile
import json
import re

clang_path = "clang-14"

script_dir = os.path.dirname(os.path.realpath(__file__))
config_file = os.path.join(script_dir, "..", "config.json")

# Directory used for temporary files. We can't always use /tmp/
# as sometimes we're blocked from running executables in there.
# (It's some security mechanism.)
cache_dir = os.path.join(script_dir, "cache")
os.makedirs(cache_dir, exist_ok=True)

# How many instructions fit into the FIFO cache.
cache_size = 16
# Number of cycles it takes to evict and load a new instruction
# into the FIFO cache.
cache_load_penalty = 40

#####################################################################
# Visualizer
#####################################################################

color_enabled = not ("NOCOLOR" in os.environ)
COLOR_END = "\033[0m" if color_enabled else ""
COLOR_BORING = "\033[36m" if color_enabled else ""
COLOR_GOOD = "\033[92m" if color_enabled else ""
COLOR_NEUTRAL = "\033[94m" if color_enabled else ""
COLOR_BAD = "\033[93m" if color_enabled else ""
COLOR_VERY_BAD = "\033[91m" if color_enabled else ""
COLOR_HEADER = "\033[95m" if color_enabled else ""
COLOR_UNDERLINE = "\033[4m" if color_enabled else ""

NO_TRIM_VAR = "NO_TRIM"
NO_HELP_VAR = "NO_HELP"


# Metadata used in the visualizer.
class LineMetaData:
    def __init__(self, line):
        # Source code of the line
        self.line = line
        # Number of cycles spent on this instruction.
        # Excludes costs of cache misses.
        self.cycles = 0
        # How often this instruction was executed.
        self.execs = 0
        # How often the I-Cache was missed.
        self.cache_misses = 0
        # Whether this line is code or something else (a variable).
        # We only profile code in BIOME.
        self.is_code = False

    # The headers of the visualizer view.
    def get_columns():
        return ["C w/0 I-Cache", "# Execs", "#IC Miss", "Total Cycles", " LLVM IR"]

    def get_description():
        desc = [
            """
Number of cycles spent on this instruction during benchmark run.
Excludes cycle cost of loading/evicting instructions from instruction cache.
""",
            """
How often this instruction was executed.
""",
            """
How often this instruction had to be loaded into instruction cache (I-cache).
Note that each executed instruction has to be loaded at least once.
""",
            """
How many cycles were spent on this instruction. This includes the cycles
spend on the instruction itself as well as I-cache load delays due to cache misses.
This is the actual number that is used to calculate your score.
""",
            """
The actual LLVM IR that is being benchmarked.
""",
        ]
        assert len(desc) == len(LineMetaData.get_columns())
        return desc

    # The headers of the view in one line with | between.
    def get_header_line():
        return "|".join(LineMetaData.get_columns())

    # The header line but without text.
    # Used to align empty non-code lines.
    def get_empty_header_line():
        result = LineMetaData.get_header_line()
        empty_line = ""
        for x in result:
            if x == "|":
                empty_line += "|"
            else:
                empty_line += " "
        # rstrip as the right field is empty (code goes there)
        return empty_line.rstrip()

    # How wide each column in our table is.
    def get_col_w(self, i):
        return len(LineMetaData.get_columns()[i])

    def _extract_inst(self) -> str:
        line = self.line
        # Remove the annotation we inserted in the instrumentation.
        # This was just used to track the instruction
        # in the source.
        needle = "!annotation !"
        # Not code, so skip it.
        if not (needle in line):
            return None
        # Return the code before the annotation (without the ', ' between).
        line = line.split(needle)[0]
        line = line.rstrip(", ")
        return line

    # The total number of cycles spent in this line of code.
    def get_total_cycles(self):
        return self.cycles + self.cache_misses * cache_load_penalty

    # The color to use when highlighting the cycle count.
    def _get_line_color(self, all_metadata):
        max_total = 1
        for l in all_metadata:
            if l.get_total_cycles() > max_total:
                max_total = l.get_total_cycles()

        percentage = self.get_total_cycles() / max_total
        if percentage > 0.9:
            return COLOR_VERY_BAD
        if percentage > 0.7:
            return COLOR_BAD
        if percentage > 0.3:
            return COLOR_NEUTRAL
        if percentage > 0.01:
            return COLOR_GOOD
        return COLOR_BORING

    def is_empty(self):
        return self.line.strip() == ""

    def get_line_report(self, all_metadata):
        inst = self._extract_inst()
        result = ""
        # Print the code.
        if inst is None or self.execs == 0:
            # Clear out stats, line is not an instruction and not interesting.
            result += LineMetaData.get_empty_header_line().rstrip()
            result += self.line
        else:
            # Print the stats before the code.
            result += self._get_line_color(all_metadata)
            result += str(self.cycles).ljust(self.get_col_w(0)) + "|"
            result += str(self.execs).ljust(self.get_col_w(1)) + "|"
            result += str(self.cache_misses).ljust(self.get_col_w(2)) + "|"

            total_cycles = self.get_total_cycles()
            result += str(total_cycles).ljust(self.get_col_w(3)) + "|"
            result += inst

        if not (NO_TRIM_VAR in os.environ):
            max_len = 110
            if len(result) > max_len:
                result = result[0:max_len] + "..."

        result += COLOR_END
        return result


# Visualizes cycle cost in a source file.
# Used for profiling source code.
class Visualizer:
    def __init__(self, input_file):
        self.line_data_in_order = []
        self.line_data_by_biome_index = {}
        self.annotation_to_biome_index = {}

        with open(input_file, "r") as f:
            lines = list(f.readlines())
            # Map annotation numbers in source to BIOME indices.
            self._create_annotation_to_index_mapping(lines)
            for line in lines:
                if self._should_hide_line(line):
                    continue
                line = line.rstrip()
                line_data = LineMetaData(line)
                self.line_data_in_order.append(line_data)

                index_match = re.search(r" !annotation !(\d+)$", line)
                if index_match:
                    index = index_match.group(1)
                    biome_index = self.annotation_to_biome_index[index]
                    line_data.is_code = True
                    self.line_data_by_biome_index[biome_index] = line_data

    def _should_hide_line(self, line):
        # This is BIOME instrumentation.
        if "@biome_info" in line:
            return True
        if '"BIOME' in line:
            return True
        # We don't care about annotations. Also some
        # annotations are from BIOME.
        if line.startswith("!"):
            return True
        # We don't care about attributes for profiling.
        if line.startswith("attributes "):
            return True
        # Hide some metadata and globals.
        if line.startswith("declare "):
            return True
        if line.startswith("target "):
            return True
        if line.startswith("@"):
            return True
        if line.startswith(";"):
            return True
        if line.startswith("source_filename ="):
            return True
        return False

    def _create_annotation_to_index_mapping(self, lines):
        for line in lines:
            result = re.search(r"!(\d+) = !{!\"BIOME-ID:(\d+)\"}", line)
            if result:
                self.annotation_to_biome_index[result.group(1)] = result.group(2)

    def report_cache_miss(self, biome_index: str):
        self.line_data_by_biome_index[biome_index].cache_misses += 1

    def report_cycle_cost(self, biome_index: str, cycles: str):
        self.line_data_by_biome_index[biome_index].cycles += cycles
        self.line_data_by_biome_index[biome_index].execs += 1

    def print_legend(self):
        print(f"\n\n{COLOR_UNDERLINE}{COLOR_HEADER}BIOME heat map:{COLOR_END}")
        print(
            f" * Note: Set environment variable '{NO_TRIM_VAR}=1' to disable trimming line of lines."
        )
        print(f" * Note: Set NOCOLOR to disable terminal color printing.")
        print(f" * Note: Set {NO_HELP_VAR} to disable this help prefix.")
        print("")
        print(f"{COLOR_HEADER}Description of columns:{COLOR_END}")
        for col, desc in zip(
            LineMetaData.get_columns(), LineMetaData.get_description()
        ):
            print(f"{COLOR_UNDERLINE}{col}{COLOR_END}: {desc}")

    def print(self, total_cycles):
        if not (NO_HELP_VAR in os.environ):
            self.print_legend()
        print("\nHeat map of program:")
        print(COLOR_UNDERLINE + LineMetaData.get_header_line() + COLOR_END)

        if len(self.line_data_in_order) == 0:
            print("No data")
            return

        # The cycles spent so far in the current BB.
        last_line = self.line_data_in_order[0]
        total_cycles_bb = 0
        for line_data in self.line_data_in_order:
            # At the end of a BB, print a summary.
            if not line_data.is_code:
                # If we have no cycles, we're somewhere in no-code part of the src.
                if total_cycles_bb != 0:
                    msg = f"{COLOR_UNDERLINE}--Total Cycles for BB above---|{total_cycles_bb}{COLOR_END} "
                    percentage = 100 * total_cycles_bb / total_cycles
                    msg += f" -- ({percentage:.2f}% of all cycles in program)"
                    print(msg)
                total_cycles_bb = 0
            else:
                total_cycles_bb += line_data.get_total_cycles()
            # Turn multiple empty lines into one.
            if last_line.is_empty() and line_data.is_empty():
                continue
            last_line = line_data
            # Print the specific line report.
            print(line_data.get_line_report(self.line_data_in_order))


#####################################################################
# Benchmarking Logic
#####################################################################


def should_rebuild(sources, target) -> bool:
    if not os.path.exists(target):
        return True

    assert isinstance(sources, list), "Needs a list of sources, not just one"

    for src in sources:
        if os.path.getmtime(src) > os.path.getmtime(target):
            return True
    return False


with open(config_file, "r") as file:
    config_json = json.load(file)
    opt_path = config_json["opt"]
    clang_path = config_json["clang"]


def get_pass_shared_object() -> str:
    output = os.path.join(script_dir, "biome-pass.so")
    if should_rebuild(
        [
            os.path.join(script_dir, "CostModel.h"),
            os.path.join(script_dir, "Instrument.cpp"),
        ],
        output,
    ):
        sp.check_call(["bash", "compile-pass.sh", output], cwd=script_dir)
        if not os.path.isfile(output):
            raise RuntimeError("Failed to compile biome pass?")
    return output


def inject_cycle_counts(tmp_dir: str, input_file: str) -> str:
    pass_so = get_pass_shared_object()
    output_file = os.path.join(tmp_dir, os.path.basename(input_file) + ".inst.ll")

    compile_args = [opt_path, "-load-pass-plugin=" + pass_so, "-S"]
    compile_args += ["-passes=biome"]
    compile_args += [input_file, "-o", output_file]

    sp.check_call(compile_args)

    return output_file


class FailedToCompile(Exception):
    pass


class FailedToRun(Exception):
    pass


class Program:
    def __init__(self, input_file, tmp_dir, extra_sources=[]):
        if input_file.endswith(".c"):
            self.input_file = tmp_dir + "/compiled.ll"

            # Warnings to disable for CSmith-generated code.
            warning_flags = [
                "-Wno-everything",
            ]

            sp.check_call(
                [clang_path, input_file, "-o", self.input_file, "-S", "-emit-llvm"]
                + warning_flags
            )
        else:
            self.input_file = input_file
        self.extra_sources = extra_sources  # type: [str]
        self.tmp_dir = tmp_dir
        self.compiled_path = None
        self.visualizer = None

    def _get_tmp_file(self, name) -> str:
        return os.path.join(self.tmp_dir, name)

    def compile_instrumented(self, visualize: bool) -> sp.CompletedProcess:
        input_lines = self.input_file
        instrumented_file = inject_cycle_counts(self.tmp_dir, input_lines)
        if visualize:
            self.visualizer = Visualizer(input_file=instrumented_file)

        self.compiled_path = self._get_tmp_file("instrumented.bin")
        args = (
            [clang_path, instrumented_file]
            + self.extra_sources
            + ["-o", self.compiled_path]
        )
        result = sp.run(args, shell=False, capture_output=True, text=True)

        if result.returncode != 0:
            raise FailedToCompile(
                f"Failed to compile {instrumented_file}:\n" + result.stderr
            )

        return result

    def parse_output(self, output: str) -> int:
        lines = output.splitlines()
        cycles = 0

        cached_instructions = []
        for line in lines:
            if not line.startswith("[CYCLE COUNT]"):
                continue
            cycles_str = line.split(" ")[3]
            parsed_cycles = int(cycles_str)
            cycles += parsed_cycles
            inst = line.strip()

            biome_index = line.split(" ")[5].strip()

            # Inform visualizer.
            if self.visualizer:
                self.visualizer.report_cycle_cost(biome_index, parsed_cycles)

            # Check for I-Cache misses.
            if not (inst in cached_instructions):
                cached_instructions.append(line.strip())
                cycles += cache_load_penalty

                # Inform visualizer.
                if self.visualizer:
                    self.visualizer.report_cache_miss(biome_index)
                if len(cached_instructions) > cache_size:
                    cached_instructions.pop(0)

        return cycles

    def profile_code(self, timeout: int, visualize: bool) -> int:
        self.compile_instrumented(visualize=visualize)

        run_result = sp.run(
            [self.compiled_path],
            shell=False,
            capture_output=True,
            text=True,
            timeout=timeout,
        )  # type: sp.CompletedProcess

        if run_result.returncode != 0:
            info = "ls: " + sp.getoutput(f"ls -alht {self.compiled_path}")
            info += "\nfile: " + sp.getoutput(f"file {self.compiled_path}")
            info += "\nnm: " + sp.getoutput(f"nm {self.compiled_path}")
            info += "\nraw out: " + sp.getoutput({self.compiled_path})
            info += "\nlldb: " + sp.getoutput(f"lldb-14 -o r -b {self.compiled_path}")
            raise FailedToRun(
                f"Failed to run {self.compiled_path}. Error output:\n"
                + run_result.stderr
                + f"\nAdditional info:\n{info}"
            )

        stdout = run_result.stdout

        cycles = self.parse_output(stdout)

        return cycles


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Benchmark program with BIOME.")
    parser.add_argument("input", type=str, help="The source file to run")
    parser.add_argument(
        "-t", "--timeout", type=int, default=30, help="Timeout (seconds)"
    )
    parser.add_argument("-v", "--visualize", action="store_true")
    args = parser.parse_args()
    with tempfile.TemporaryDirectory(dir=cache_dir) as tmp:
        program = Program(input_file=args.input, tmp_dir=tmp)
        cycle_count = program.profile_code(
            timeout=args.timeout, visualize=args.visualize
        )
        if program.visualizer:
            program.visualizer.print(cycle_count)
        else:
            print("SCORE:" + str(cycle_count))
