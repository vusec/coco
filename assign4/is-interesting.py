#!/usr/bin/env python3

import argparse
import os
import sys
import subprocess
import tempfile
import shutil

# ./is-interesting.py -i tests/GVN.c -p ExampleBrokenPass
# Define the passes and other needed paths
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

def generate_random_c_program() -> str:
    random_program = "random_program.c"
    try:
        # Run Csmith to generate a random C program
        subprocess.run(["csmith", "--output", random_program], check=True)
        return random_program
    except subprocess.CalledProcessError as e:
        print(f"Error generating random C program: {e}", file=sys.stderr)
        sys.exit(1)

def run_program(input_file: str, output_file: str) -> str:
    try:
        result = subprocess.run([input_file], check=True, text=True, capture_output=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return str(e)

def is_source_interesting(src: str, pass_name: str) -> bool:
    
    with tempfile.NamedTemporaryFile(delete=False) as pre_opt_file, \
         tempfile.NamedTemporaryFile(delete=False) as post_opt_file:

        pre_opt_output = f"{pre_opt_file.name}.out"
        post_opt_output = f"{post_opt_file.name}.out"
        
        command = ["sudo", "./optimize.sh", src, "output.bin", pass_name]
        subprocess.run(command, check=True, text=True, capture_output=True)

        pre_opt_result = run_program("./output.bin.unoptimized", pre_opt_output)
        post_opt_result = run_program("./output.bin.optimized", post_opt_output)

        if pre_opt_result != post_opt_result:
            print(f"Optimizer bug detected: Outputs differ between unoptimized and optimized versions!")
            return True
        else:
            print(f"No bug detected: Outputs are the same.")
            return False

# Main function to execute the script
def main():
    parser = argparse.ArgumentParser(description="Check if the source code demonstrates an optimizer bug.")
    parser.add_argument('-i', '--input', required=True, help='Source file to test', type=str)
    parser.add_argument('-p', '--optpass', required=False, help='Optimization pass to test', type=str, choices=passes, default="None")
    args = parser.parse_args()
    generate_random_c_program()
    
    try:
        if is_source_interesting(args.input, args.optpass):
            sys.exit(0)
    except subprocess.TimeoutExpired as e:
        print(f"Timeout running command: {str(e)}", file=sys.stderr)
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {str(e)}", file=sys.stderr)

    sys.exit(1)

if __name__ == "__main__":
    main()
