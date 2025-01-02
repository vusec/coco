#!/usr/bin/env python

import getpass
import os
import subprocess as sp
import sys
import json
import socket

grade_dir = os.path.dirname(os.path.realpath(__file__))
base_dir = os.path.realpath(os.path.join(grade_dir, "..", ".."))

# Timeout in seconds for each individual test.
grade_timeout = 20

# Grade output to a file
grade_out_var = "GRADE_OUTPUT"
grade_output_json = None
if grade_out_var in os.environ:
    grade_output_json = os.environ[grade_out_var]
    del os.environ[grade_out_var]

# Terminal color support.
color_enabled = not ("NOCOLOR" in os.environ)
COLOR_ERR = "\033[91m" if color_enabled else ""
COLOR_END = "\033[0m" if color_enabled else ""
COLOR_INFO = "\033[96m" if color_enabled else ""
COLOR_HEADER = "\033[95m" if color_enabled else ""
COLOR_OK = "\033[92m" if color_enabled else ""
COLOR_WARN = "\033[0;34m" if color_enabled else ""


task_to_assignment_folder = {
    "1": "assign1/",
    "2": "assign2/",
    "3": "assign3/",
    "4": "assign4/",
}


def is_in_codegrade():
    return getpass.getuser() == "codegrade"


def assert_in_container():
    disable_env_var = "DISABLE_COCO_CHECK"
    if disable_env_var in os.environ:
        return

    hostname = socket.gethostname()
    if hostname != "coco":
        msg = COLOR_WARN + "warning: " + COLOR_END
        msg += "You don't seem to be within the course docker container. Aborting command.\n"
        msg += "Run ./run.py to start the right docker environment shell.\n"
        msg += COLOR_INFO + "note: " + COLOR_END
        msg += f"prefix the command with {disable_env_var}=1 to disable this check."
        msg += " You should only do this if you know what you're getting into."
        print(msg)
        sys.exit(1)


assert_in_container()


def get_clang_binary() -> str:
    config_file = os.path.join(base_dir, "framework", "config.json")

    with open(config_file, "r") as file:
        config_json = json.load(file)
        return config_json["clang"]


def get_opt_binary() -> str:
    config_file = os.path.join(base_dir, "framework", "config.json")

    with open(config_file, "r") as file:
        config_json = json.load(file)
        return config_json["opt"]


def should_rebuild(sources, target) -> bool:
    if not os.path.exists(target):
        return True

    assert isinstance(sources, list), "Needs a list of sources, not just one"

    for src in sources:
        if os.path.getmtime(src) > os.path.getmtime(target):
            return True
    return False


class TestCase:
    def __init__(self, path, name):
        self.path = path
        self.name = name


class Assignment:
    def __init__(self, basedir, args):
        self.good_tests = 0
        self.total_tests = 0

        self.good_safeguard_tests = 0
        self.total_safeguard_tests = 0

        self.current_test_is_safeguard = False
        self.basedir = basedir
        self.filter = args.filter

    def report_test_start(self, test_name, is_safeguard=False):
        self.current_test_is_safeguard = is_safeguard
        safeguard_str = ""
        if is_safeguard:
            self.total_safeguard_tests += 1
            safeguard_str = " (Safeguard test)"
        else:
            self.total_tests += 1
        sys.stdout.write(
            COLOR_HEADER
            + " * "
            + COLOR_END
            + test_name
            + COLOR_HEADER
            + f"{safeguard_str}: "
            + COLOR_END
        )
        sys.stdout.flush()

    def report_test_pass(self):
        if self.current_test_is_safeguard:
            self.good_safeguard_tests += 1
        else:
            self.good_tests += 1
        print(COLOR_OK + "OK" + COLOR_END)

    def report_error(self, msg):
        print(COLOR_ERR + "ERR\n [Grading Script Error]: " + COLOR_END + msg)

    def rebuild_passes(self, basedir, note="", targets=[]):
        self.start_test_section("Rebuilding passes" + note)
        sp.check_call(["make"] + targets, cwd=basedir)

    def list_tests(self, dir, suffix=".c"):
        dir = self.basedir + "/" + dir
        result = []
        files = list(os.listdir(dir))
        files.sort()
        for f in files:
            if f.endswith(suffix):

                full = os.path.realpath(os.path.join(dir, f))
                relpath = os.path.relpath(full, self.basedir)
                if self.filter in relpath:
                    result += [TestCase(path=full, name=relpath)]
        return result

    def start_test_section(self, name):
        print(name)

    def get_output(self, binary) -> str:
        result = sp.run(binary, stdout=sp.PIPE, stderr=sp.STDOUT, timeout=grade_timeout)
        return result.stdout.decode("utf-8")

    def expect_exit_code(self, cmd, expected: int) -> bool:
        result = sp.run(
            cmd, shell=False, stdout=sp.PIPE, stderr=sp.STDOUT, timeout=grade_timeout
        )
        if result.returncode != expected:
            msg = f"Expected return code {expected} but got {result.returncode}."
            msg += COLOR_INFO + "\n Command: " + COLOR_END + " ".join(cmd)
            msg += COLOR_INFO + "\n Script output:\n" + COLOR_END
            msg += result.stdout.decode("utf-8")
            self.report_error(msg)
            return False
        return True

    def give_grade_with_score(self, assignment_name, points, max_points):
        if not self.can_give_grade():
            return

        # Clamp to 0 and max points.
        raw_points = sorted([0, points, max_points])[1]
        # Round down to the closest full point.
        points = int(raw_points)

        msg = f"Final grade for assignment {assignment_name}: {points:.1f} of {max_points} pts"
        print(msg)

        if grade_output_json:
            with open(grade_output_json, "w") as out:
                out.write(f'{{ "tag": "points", "points": "{points}/{max_points}" }}\n')

    def can_give_grade(self):
        if self.filter:
            print("No grade given as test filter was set ('-f' flag)")
            return False
        return True

    def give_grade(self, assignment_name, max_points):
        if self.total_tests == 0:
            self.report_error("Did not run any tests?")
            return

        assert self.good_tests <= self.total_tests, "More good tests than ran?"

        percentage = self.good_tests / self.total_tests
        percentage_100 = percentage * 100
        points = percentage * max_points

        # Deduct 0.5 points for each failed safeguard test failed.
        bad_safeguard_tests = self.total_safeguard_tests - self.good_safeguard_tests
        safeguard_points_reduction = bad_safeguard_tests * 0.5
        points -= safeguard_points_reduction
        if points < 0:
            points = 0

        print(
            f"\n{self.good_tests} out of {self.total_tests} tests passed ({percentage_100:.1f}%)"
        )
        if bad_safeguard_tests != 0:
            print(
                f"{bad_safeguard_tests} safeguard tests failed! Reducing score by {safeguard_points_reduction} points."
            )
        self.give_grade_with_score(assignment_name, points, max_points)
