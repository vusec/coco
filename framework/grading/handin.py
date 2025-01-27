#!/usr/bin/env python3

from grade_utils import *

import argparse
import subprocess as sp

skipped_suffixes = [
    "/tests",
    "/benchmarks",
    "/original-src",
    ".so",
    ".o",
    ".gitignore",
    ".md",
    "opt-tmp",
    "__pycache__",
]

# The tests for assignment 4 are part of the submission.
always_included_suffixes = [
    "assign4/tests"
]

def _should_handin_file(path):
    for s in always_included_suffixes:
        if path.endswith(s):
            return True
    for s in skipped_suffixes:
        if path.endswith(s):
            return False
    return True


def create_handin(task):
    os.chdir(base_dir)
    assign_folder = task_to_assignment_folder[task]

    files_to_zip = []
    for f in os.listdir(assign_folder):
        file_path = os.path.join(assign_folder, f)
        if _should_handin_file(file_path):
            files_to_zip.append(file_path)

    zip_name = f"handin-{task}.zip"
    if os.path.isfile(zip_name):
        os.remove(zip_name)
    sp.check_call(["zip", "-r", zip_name] + files_to_zip)
    print(f"You need to upload {zip_name} on Canvas to submit the assignment.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Create handin zip files.")
    parser.add_argument(
        "-a",
        "--assignment",
        required=True,
        help="Which assignment to run",
        choices=task_to_assignment_folder.keys(),
    )
    args = parser.parse_args()

    create_handin(args.assignment)
