#!/usr/bin/env python3

import argparse
import os

from grade_utils import *

compile_sh = os.path.join(base_dir, "assign1", "compile.sh")


def grade_parser(args):
    a = Assignment(base_dir + "/assign1/tests/", args=args)
    a.start_test_section("Checking programs invalid syntax")
    for t in a.list_tests("parsing/bad/"):
        a.report_test_start(t.name)
        if a.expect_exit_code([compile_sh, t.path, "/tmp/out.ll"], 2):
            a.report_test_pass()

    a.start_test_section("Checking programs with valid syntax")
    for t in a.list_tests("code-gen/"):
        a.report_test_start(t.name, is_safeguard=True)
        if a.expect_exit_code([compile_sh, t.path, "/tmp/out.ll"], 0):
            a.report_test_pass()

    a.give_grade("1.1", 2)


def grade_type_checker(args):
    a = Assignment(base_dir + "/assign1/tests/", args=args)

    a.start_test_section("Checking programs invalid semantics")
    for t in a.list_tests(dir="type-checking/bad/"):
        a.report_test_start(t.name)
        if a.expect_exit_code([compile_sh, t.path, "/tmp/out.ll"], 2):
            a.report_test_pass()

    a.start_test_section("Type checking valid programs")
    for t in a.list_tests(dir="code-gen/"):
        a.report_test_start(t.name, is_safeguard=True)
        if a.expect_exit_code([compile_sh, t.path, "/tmp/out.ll"], 0):
            a.report_test_pass()

    a.give_grade("1.2", 3)


def grade_ir_gen(args):
    a = Assignment(base_dir + "/assign1/tests/", args=args)

    runtime_file = os.path.realpath(base_dir + "/framework/fennec/FenneC_IO.c")

    for t in a.list_tests(dir="code-gen/"):
        a.report_test_start(t.name)
        test_input = t.path
        ll_file = test_input + ".ll"
        binary = test_input + ".bin"
        output_file = test_input + ".expected_output"

        # Generate the expected output if it doesn't exist.
        if not os.path.exists(output_file):
            clang_args = [get_clang_binary(), test_input, "-o", binary, runtime_file]
            clang_args += ["-I", base_dir + "/framework/fennec/"]
            clang_args += ["-fsanitize=undefined", "-fno-sanitize-recover=all"]
            if not a.expect_exit_code(clang_args, 0):
                continue

            clang_output = a.get_output([binary])
            with open(output_file, "w") as f:
                f.write(clang_output)

        with open(output_file, "r") as f:
            expected_output = f.read()

        # Run frontend (this is what the student is writing).
        if not a.expect_exit_code([compile_sh, test_input, ll_file], 0):
            continue

        # Link frontend with backend.
        if not a.expect_exit_code(
            [get_clang_binary(), ll_file, "-o", binary, runtime_file], 0
        ):
            continue

        actual_output = a.get_output([binary])
        if actual_output != expected_output:
            msg = "Output from binary doesn't match expected output.\n"
            msg += "> Got output:\n" + actual_output
            msg += "> Expected output:\n" + expected_output
            a.report_error(msg)
            continue

        a.report_test_pass()

    a.give_grade("1.3", 5)
