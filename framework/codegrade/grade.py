#!/bin/bash

import getpass
import shutil as sh
import subprocess as sp
import sys
import os
import random

# This script is executed on codegrade when testing a task.
# Task is specified by the first command argument.

def error_out(msg):
    print("error: " + msg)
    sys.exit(1)

assignment = sys.argv[1]
task = sys.argv[2]
grade_dir = os.path.dirname(os.path.realpath(__file__))
base_dir = os.path.realpath(os.path.join(grade_dir, "..", ".."))

if getpass.getuser() != "codegrade":
    print("This is supposed to run on the codegrade environment. Exiting...")
    sys.exit(1)

os.chdir(base_dir)

home_dir = "/home/codegrade/"
handin_dir = home_dir + "student/"
student_coco = home_dir + "/student-coco/"

# Create a fresh student dir.
if os.path.isdir(student_coco):
    sh.rmtree(student_coco)
os.makedirs(student_coco)
# Copy the handin into the student coco directory.
assign_dir = student_coco + f"/assign{assignment}/"
sh.copytree(handin_dir, assign_dir)

# Restore a bunch of files to their original state.
to_replace_list = [
    "/framework",
    "/assign1/tests",
    "/assign2/benchmarks",
    "/assign3/tests",
    "/assign4/tests",
    "/assign4/original-src",
    "/run.py",
    "/grade",
]

for to_replace in to_replace_list:
    src = base_dir + to_replace
    dest = student_coco + to_replace

    if os.path.isfile(dest):
        os.remove(dest)
    if os.path.isdir(dest):
        sh.rmtree(dest)

    if os.path.isfile(src):
        sh.copy(src, dest)
    else:
        sh.copytree(src, dest)

# We don't know what needs to be executable, so just mark the whole submission.
sp.check_call(["chmod", "-R", "755", student_coco])

# Pick a random grade file.
# This isn't fool proof and student's could still fake a grade
# output file. In the end, it's just important to make this more
# annoying to do than the actual assignments.
grade_file = "grade-out-" + str(random.randrange(0, 10000000)) + ".json"

run_py = os.path.join(student_coco, "run.py")
cmd = [run_py, "--nobuild", "--nosudo", "-c"]
# This is one string as it's passed to the shell in docker.
cmd += [f'PRINT_DIFF=1 NOCOLOR=1 GRADE_OUTPUT={grade_file} ./grade -a ' + task]
sp.check_call(cmd, cwd=student_coco)

# Copy the grade file from the agreed
sh.copy(os.path.join(student_coco, grade_file), os.path.join(home_dir, "grade.json"))
