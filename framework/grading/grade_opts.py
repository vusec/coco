#!/usr/bin/env python3

import os
import json
import subprocess as sp
import statistics

from grade_utils import *

biome_path = os.path.join(base_dir, "framework", "BIOME", "biome.py")
optimize_path = os.path.join(base_dir, "assign2", "optimize.sh")

clean_config = "CLEAN_CONFIG" in os.environ


def get_score_for_source(src: str) -> int:
    output = sp.check_output([biome_path, src], timeout=grade_timeout).decode("utf-8")
    prefix = "SCORE:"
    for line in output.splitlines():
        if line.startswith(prefix):
            score_str = line[len(prefix) :].strip()
            return int(score_str)


class Benchmark:
    def __init__(self, a: Assignment, name: str, source: str):
        self.name = name
        self.source = source
        self.unopt_bin = self.source + ".unopt.bin"
        self.opt_bin = self.source + ".opt.bin"
        self.ll_source = self.source + ".ll"
        self.opt_source = self.source + ".opt.ll"
        self.config_file = source + ".json"
        self.base_score = 0  # type: int
        self.perfect_score = 0  # type: int
        self.measured_score = 0  # type: int
        self.assignment = a

        self.output_file = self.source + ".expected_output"
        self._create_ll_source()
        sp.check_call(
            [optimize_path, self.ll_source, self.opt_source], timeout=grade_timeout
        )

    def do_benchmark(self):
        self._measure_score()

        if not os.path.exists(self.config_file) or clean_config:
            self._create_default_config()
            if clean_config:
                if self.base_score <= self.measured_score:
                    raise RuntimeError(
                        f"Benchmark could not be optimized: {self.base_score} -> {self.measured_score}"
                    )

        with open(self.config_file, "r") as file:
            self.config = json.load(file)
            self.base_score = self.config["baseScore"]
            self.perfect_score = self.config["perfectScore"]

    def _create_ll_source(self):
        if should_rebuild([self.source], self.ll_source):
            tmp_out = self.ll_source + ".pre-mem2reg.ll"
            extra_args = ["-S", "-emit-llvm", "-Xclang", "-disable-O0-optnone"]
            # Fix the many redundant warnings in valid csmith code.
            if "csmith/csmith" in self.source:
                extra_args += ["-Wno-everything"]
            sp.check_call([get_clang_binary(), self.source, "-o", tmp_out] + extra_args)
            sp.check_call(
                [
                    get_opt_binary(),
                    "-passes=mem2reg",
                    "-S",
                    tmp_out,
                    "-o",
                    self.ll_source,
                ]
            )
            os.remove(tmp_out)

    def _create_expected_output(self):
        if should_rebuild([self.ll_source], self.output_file):
            clang_args = [get_clang_binary(), self.ll_source, "-o", self.unopt_bin]
            if not self.assignment.expect_exit_code(clang_args, 0):
                raise RuntimeError(
                    f"Failed to compile benchmark {self.source}."
                    + " Did you modify the source?"
                )

            clang_output = self.assignment.get_output([self.unopt_bin])
            with open(self.output_file, "w") as f:
                f.write(clang_output)

        with open(self.output_file, "r") as f:
            self.expected_output = f.read()

    def is_optimized_output_correct(self) -> bool:
        self._create_expected_output()
        clang_args = [get_clang_binary(), self.opt_source, "-o", self.opt_bin]
        if not self.assignment.expect_exit_code(clang_args, 0):
            raise RuntimeError(
                f"Failed to compile benchmark {self.source}."
                + " Did you modify the source?"
            )

        clang_output = self.assignment.get_output([self.opt_bin])
        if clang_output != self.expected_output:
            self.assignment.report_error(
                "Output changed after optimization. "
                + "Your pass is changing program behavior which is wrong.\n"
                + f"Expected program output:\n{self.expected_output}\n\n"
                + f"Your program output:\n{clang_output}\n\n"
            )
            return False
        return True

    def _measure_score(self):
        self.measured_score = get_score_for_source(self.opt_source)

    def _create_default_config(self):
        self.base_score = get_score_for_source(self.ll_source)

        with open(self.config_file, "w") as file:
            json.dump(
                {"baseScore": self.base_score, "perfectScore": self.measured_score},
                file,
            )

    def _update_config(self):
        with open(self.config_file, "w") as file:
            json.dump(
                {"baseScore": self.base_score, "perfectScore": self.measured_score},
                file,
            )

    def get_percentage_improvement(self) -> float:
        perfect_diff = self.base_score - self.perfect_score
        actual_diff = self.base_score - self.measured_score
        if actual_diff == perfect_diff:
            return 1
        percent_diff = actual_diff / perfect_diff
        return percent_diff

    def get_score_str(self) -> str:
        percent_diff = self.get_percentage_improvement() * 100

        color = COLOR_ERR
        if percent_diff <= 20:
            pass
        elif percent_diff > 80:
            color = COLOR_OK
        else:
            color = COLOR_WARN
        result = f"{color}{percent_diff:.1f}%{COLOR_END} of ideal performance."
        result += f"\n      Detailed runtimes in cycles: Unopt={self.base_score}, Opt={self.measured_score}, Perfect={self.perfect_score}"

        return result


def grade_optimizations(args):
    a = Assignment(base_dir + "/assign2/benchmarks/", args=args)
    a.rebuild_passes(
        base_dir + "/assign2/", " (This might take a while the first time)"
    )

    a.start_test_section("Benchmarking simple tests")

    failed_tests = 0

    total_improvements = []

    for t in a.list_tests("simple/"):
        a.report_test_start(t.name)
        try:
            bench = Benchmark(a, t.name, t.path)
            bench.do_benchmark()
            percentage_improved = bench.get_percentage_improvement()
            total_improvements += [percentage_improved if percentage_improved <= 1 else 1]
            print(bench.get_score_str())
            if not bench.is_optimized_output_correct():
                failed_tests += 1
        except sp.CalledProcessError as e:
            a.report_error("Failed to run command: " + " ".join(e.cmd))
            failed_tests += 1

    if not clean_config:
        a.start_test_section(
            "Benchmarking large random programs\n"
            + "  (These test your passes for correctness)."
        )
        for t in a.list_tests("csmith/"):
            a.report_test_start(t.name)
            try:
                bench = Benchmark(a, t.name, t.path)
                if not bench.is_optimized_output_correct():
                    failed_tests += 1
                else:
                    a.report_test_pass()
            except sp.CalledProcessError as e:
                a.report_error("Failed to run command: " + " ".join(e.cmd))
                failed_tests += 1

    score = statistics.fmean(total_improvements)
    # Deduct 2 for each failed test.
    failed_test_score = 2 * failed_tests
    # Clamp to 0 to 1
    score -= failed_test_score
    score = sorted([0, score, 1])[1] * 10
    int_score = int(score)

    print(f"Note: Raw score is {score:.2f}, but is rounded down for final score\n")
    if failed_tests != 0:
        print(f"Warning: You lost {failed_test_score} points due to miscompilations.")
    a.give_grade_with_score("4", int_score, 10)
