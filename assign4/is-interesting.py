#!/usr/bin/env python3

import argparse
import os
import sys
import tempfile
import subprocess as sp


src_dir = os.path.dirname(os.path.realpath(__file__))
optimize_sh = os.path.join(src_dir, "optimize.sh")
has_ub = os.path.join(src_dir, "has-ub.py")
timeout = 3

# Hints:
# * optimize_sh takes a C source file as the first argument and produces an
#   optimized binary (second argument) using the pass (third argument).
#   E.g.,: optimize.sh ./input.c output_binary GVN.
# * has-ub.py returns exit code 0 if the program is (probably) free of UB.

def is_source_interesting(src : str, pass_name : str) -> bool:
    with tempfile.TemporaryDirectory() as tmpdir:
        # implementation goes here
        return False

passes = [
    "None",
    "ExampleBrokenPass",
    "GVN",
    "GVN.original",
    "GlobalOpt",
    "GlobalOpt.original",
    "InstSimplify",
    "InstSimplify.original",
]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Determines whether the given source demonstrates a optimizer bug.")
    parser.add_argument('-i', '--input', required=True, help='Which assignment to run', type=str)
    parser.add_argument('-p', '--optpass', required=False, help='The optimization pass to run', type=str, choices=passes)
    args = parser.parse_args()

    try:
        if is_source_interesting(args.input, args.optpass):
            sys.exit(0)
    except sp.TimeoutExpired as e:
        print("Timeout running command: " + str(e))
    except sp.CalledProcessError as e:
        print("Error running command: " + str(e))
    sys.exit(1)