from grade_utils import *

compile_path = os.path.join(base_dir, "assign4", "optimize.sh")
interesting_script = os.path.join(base_dir, "assign4", "is-interesting.py")

assignment_dir = base_dir + "/assign4/"

broken_pass_name = "ExampleBrokenPass"

minimized_test_size = 300


def is_interesting(assignment: Assignment, src, opt_pass) -> bool:
    args = [interesting_script, "-i", src, "-p", opt_pass]
    result = sp.run(args, stdout=sp.PIPE, stderr=sp.STDOUT, timeout=grade_timeout)
    code = result.returncode
    if code == 1:
        return False
    if code == 0:
        return True

    output = result.stdout.decode("utf-8")
    args_str = " ".join(args)
    assignment.report_error(
        f"Exit code from interesting test is not 1 or 0, "
        + f"but {code}.\n  Command{args_str}\n"
        + f"  Script output:\n{output}"
    )
    return False


def grade_test_script(args):
    a = Assignment(assignment_dir, args=args)
    a.rebuild_passes(assignment_dir, targets=["ExampleBrokenPass.so"])

    broken_sanity_test = "tests/simple-load.c"
    broken_sanity_test_path = assignment_dir + "/" + broken_sanity_test

    ub_test = "tests/invalid-test.c"
    ub_test_path = assignment_dir + "/" + ub_test

    a.report_test_start(broken_sanity_test + " with no pass")
    if is_interesting(a, broken_sanity_test_path, "None"):
        a.report_error(
            broken_sanity_test
            + " should not be considered interesting with 'None' pass."
        )
    else:
        a.report_test_pass()

    a.report_test_start(broken_sanity_test + " with no broken pass")
    if not is_interesting(a, broken_sanity_test_path, broken_pass_name):
        a.report_error(
            broken_sanity_test
            + f" should be considered interesting with '{broken_pass_name}' pass."
        )
    else:
        a.report_test_pass()

    a.report_test_start(ub_test + " to check for ub check")
    if is_interesting(a, ub_test_path, broken_pass_name):
        a.report_error(
            ub_test
            + f" is undefined/non-deterministic, and should not be considered interesting."
        )
    else:
        a.report_test_pass()

    a.give_grade("4.1", 1)


def grade_broken_pass(args, assignment_name, pass_name):
    a = Assignment(assignment_dir, args=args)
    a.rebuild_passes(
        assignment_dir, targets=[pass_name + ".so", pass_name + ".original.so"]
    )

    example_path = "tests/" + pass_name + ".c"
    full_example_path = assignment_dir + "/" + example_path

    was_test_valid = False

    a.report_test_start(
        f"Checking if test is demonstrating optimizer bug: {example_path}"
    )
    if is_interesting(a, full_example_path, pass_name + ".original"):
        a.report_test_pass()
        was_test_valid = True
    else:
        a.report_error(f"{example_path} not considered interesting.")

    a.report_test_start(f"Checking if is minimized: {example_path}")
    test_size = os.path.getsize(full_example_path)
    if test_size <= minimized_test_size:
        if was_test_valid:
            a.report_test_pass()
        else:
            a.report_error(
                f"Test {example_path} appears minimized, but is "
                + "not demonstrating an optimizer bug"
            )
    else:
        a.report_error(
            f"Test {example_path} is {test_size}B large, but "
            + f"a minimized test case needs to be smaller than "
            + f"{minimized_test_size}B."
        )

    a.report_test_start(f"Checking if pass is fixed: {example_path}")
    if not is_interesting(a, full_example_path, pass_name):
        if was_test_valid:
            a.report_test_pass()
        else:
            a.report_error(f"Skipped as pass as test case above was not interesting.")
    else:
        a.report_error(f"Pass still seems to have optimizer bug.")

    a.give_grade(assignment_name, 3)


def grade_pass_simplify(args):
    grade_broken_pass(args, "4.2", "InstSimplify")


def grade_pass_global_opt(args):
    grade_broken_pass(args, "4.3", "GlobalOpt")


def grade_pass_gvn(args):
    grade_broken_pass(args, "4.4", "GVN")
