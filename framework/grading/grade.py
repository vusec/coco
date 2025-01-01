#!/usr/bin/env python3

import argparse
import os

from grade_utils import *

import grade_frontend
import grade_opts
import grade_safety
import grade_bugs

# Maps assignments to the grading parts.
assignment_map = {
    "1.1": grade_frontend.grade_parser,
    "1.2": grade_frontend.grade_type_checker,
    "1.3": grade_frontend.grade_ir_gen,
    "2": grade_opts.grade_optimizations,
    "3.1": grade_safety.grade_bounds_heap,
    "3.2": grade_safety.grade_bounds_stack,
    "3.3": grade_safety.grade_use_after_free,
    "4.1": grade_bugs.grade_test_script,
    "4.2": grade_bugs.grade_pass_simplify,
    "4.3": grade_bugs.grade_pass_global_opt,
    "4.4": grade_bugs.grade_pass_gvn,
}

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Automatically grades assignments.")
    parser.add_argument(
        "-a",
        "--assignment",
        required=True,
        help="Which assignment to run",
        choices=assignment_map.keys(),
    )
    parser.add_argument(
        "-f",
        "--filter",
        required=False,
        help="Filter for tests to run (matches on file path)",
        type=str,
        default="",
    )
    args = parser.parse_args()

    assignment = assignment_map[args.assignment]
    assignment(args)
