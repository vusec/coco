#!/usr/bin/env python3

import subprocess as sp
import os
import argparse
import tempfile
import json

clang_path = "clang-14"

script_dir = os.path.dirname(os.path.realpath(__file__))
config_file = os.path.join(script_dir, "..", "config.json")

# Directory used for temporary files. We can't use /tmp/ as we can't
# run executables stored in there.
cache_dir = os.path.join(script_dir, "cache")
os.makedirs(cache_dir, exist_ok=True)

cache_size = 16
cache_load_penalty = 40

def should_rebuild(sources, target) -> bool:
    if not os.path.exists(target):
        return True
    
    assert isinstance(sources, list), "Needs a list of sources, not just one"

    for src in sources:
        if os.path.getmtime(src) > os.path.getmtime(target):
            return True
    return False

with open(config_file, 'r') as file:
    config_json = json.load(file)
    opt_path = config_json["opt"]
    clang_path = config_json["clang"]

def get_pass_shared_object() -> str:
    output = os.path.join(script_dir, "biome-pass.so")
    if should_rebuild([os.path.join(script_dir, "CostModel.h"),
                       os.path.join(script_dir, "Instrument.cpp")],
                       output):
        sp.check_call(["bash", "compile-pass.sh", output], cwd=script_dir)
        if not os.path.isfile(output):
            raise RuntimeError("Failed to compile biome pass?")
    return output

def inject_cycle_counts(tmp_dir : str, input_file : str) -> str:
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
    def __init__(self, input_file, tmp_dir, extra_sources = []):
        if input_file.endswith(".c"):
            self.input_file = tmp_dir + "/compiled.ll"

            # Warnings to disable for CSmith-generated code.
            warning_flags = [
                "-Wno-everything",
            ]

            sp.check_call([clang_path, input_file, "-o", self.input_file, "-S", "-emit-llvm"] + warning_flags)
        else:
            self.input_file = input_file
        self.extra_sources = extra_sources # type: [str]
        self.tmp_dir = tmp_dir
        self.compiled_path = None

    def _get_tmp_file(self, name) -> str:
        return os.path.join(self.tmp_dir, name)

    def compile_instrumented(self) -> sp.CompletedProcess:
        input_lines = self.input_file
        instrumented_file = inject_cycle_counts(self.tmp_dir, input_lines)

        self.compiled_path = self._get_tmp_file("instrumented.bin")
        args = [clang_path, instrumented_file] + self.extra_sources + ["-o", self.compiled_path]
        result = sp.run(args, shell=False, capture_output = True, text = True)

        if result.returncode != 0:
            raise FailedToCompile(f"Failed to compile {instrumented_file}:\n"
                                  + result.stderr)

        return result
    
    def parse_output(self, output : str) -> int:
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
            if not (inst in cached_instructions):
                cached_instructions.append(line.strip())
                cycles += cache_load_penalty
                if len(cached_instructions) > cache_size:
                    cached_instructions.pop(0)
    
        return cycles

    def profile_code(self, timeout : int) -> int:
        self.compile_instrumented()

        run_result = sp.run([self.compiled_path], shell=False,
                            capture_output = True, text = True, timeout = timeout) # type: sp.CompletedProcess

        if run_result.returncode != 0:
            info = "ls: " + sp.getoutput(f"ls -alht {self.compiled_path}")
            info += "\nfile: " + sp.getoutput(f"file {self.compiled_path}")
            info += "\nnm: " + sp.getoutput(f"nm {self.compiled_path}")
            info += "\nraw out: " + sp.getoutput({self.compiled_path})
            info += "\nlldb: " + sp.getoutput(f"lldb-14 -o r -b {self.compiled_path}")
            raise FailedToRun(f"Failed to run {self.compiled_path}. Error output:\n"
                              + run_result.stderr + f"\nAdditional info:\n{info}")
        
        stdout = run_result.stdout

        cycles = self.parse_output(stdout)

        return cycles

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Benchmark program with BIOME.")
    parser.add_argument('input', type=str, help='The source file to run')
    parser.add_argument('-t', '--timeout', type=int, default=30, help='Timeout (seconds)')
    args = parser.parse_args()
    with tempfile.TemporaryDirectory(dir=cache_dir) as tmp:
        program = Program(input_file=args.input, tmp_dir=tmp)
        cycle_count = program.profile_code(timeout=args.timeout)
        print("SCORE:" + str(cycle_count))