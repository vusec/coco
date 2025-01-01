from grade_utils import *

sanitize_path = os.path.join(base_dir, "assign3", "sanitize.sh")
runtime_path = os.path.join(base_dir, "assign3", "Runtime.so")


def check_valid_program(a: Assignment, src: str):
    src_ll = src + ".ll"
    sanitized_ll = src + ".sanitized.ll"
    sanitized_binary = src + ".sanitized.bin"
    normal_binary = src + ".default.bin"

    if should_rebuild([get_clang_binary(), src], src_ll):
        sp.check_call(
            [
                get_clang_binary(),
                src,
                "-o",
                src_ll,
                "-S",
                "-emit-llvm",
                "-Xclang",
                "-disable-O0-optnone",
                "-g",
            ]
        )

    if should_rebuild([get_clang_binary(), src_ll], normal_binary):
        sp.check_call([get_clang_binary(), src_ll, "-o", normal_binary])

    sp.check_call([sanitize_path, src_ll, sanitized_ll], timeout=grade_timeout)
    sp.check_call(
        [
            get_clang_binary(),
            sanitized_ll,
            runtime_path,
            "-o",
            sanitized_binary,
            "-g",
            "-fstandalone-debug",
        ]
    )

    try:
        sanitized_output = sp.check_output([sanitized_binary])
    except sp.CalledProcessError as e:
        a.report_error(
            f"Sanitized binary of valid program unexpectedly crashes? Running {sanitized_binary} should not produce an error."
        )
        return
    normal_output = sp.check_output([normal_binary])

    if sanitized_output != normal_output:
        a.report_error(
            "Program output changed for valid program after sanitizer is applied."
            + f"Normal output:\n{normal_output}\nSanitized output:\n{sanitized_output}\n"
        )
    else:
        a.report_test_pass()


def test_valid_progs(a: Assignment):
    a.start_test_section("Benchmarking valid programs without bugs")
    for t in a.list_tests("valid/"):
        a.report_test_start(t.name, is_safeguard=True)
        try:
            check_valid_program(a, t.path)
        except sp.CalledProcessError as e:
            a.report_error(str(e))


def check_exit_code_for_source(assignment: Assignment, src):
    src_ll = src + ".ll"
    sanitized_ll = src + ".sanitized.ll"
    binary = src + ".sanitized.bin"

    if should_rebuild([get_clang_binary(), src], src_ll):
        sp.check_call(
            [
                get_clang_binary(),
                src,
                "-Wno-everything",
                "-o",
                src_ll,
                "-S",
                "-emit-llvm",
                "-Xclang",
                "-disable-O0-optnone",
            ]
        )

    sp.check_call([sanitize_path, src_ll, sanitized_ll])
    sp.check_call([get_clang_binary(), sanitized_ll, runtime_path, "-o", binary])
    result = sp.run(
        [binary], stdout=sp.PIPE, stderr=sp.STDOUT
    )  # type: sp.CompletedProcess
    code = result.returncode

    if code == 66:
        assignment.report_test_pass()
        return

    output = result.stdout.decode("utf-8")
    assignment.report_error(
        f"Exit code {code} from binary "
        + "is not 66 (the expected exit code for sanitizer"
        + f" errors).\nBinary output:\n{output}"
    )


def grade_bounds_heap(args):
    a = Assignment(base_dir + "/assign3/tests/", args=args)
    a.rebuild_passes(base_dir + "/assign3/")

    a.start_test_section("Testing heap buffer overflow tests")
    for t in a.list_tests("heap/"):
        a.report_test_start(t.name)
        check_exit_code_for_source(a, t.path)

    test_valid_progs(a)
    a.give_grade("3.1", 4)


def grade_bounds_stack(args):
    a = Assignment(base_dir + "/assign3/tests/", args=args)
    a.rebuild_passes(base_dir + "/assign3/")

    a.start_test_section("Testing stack buffer overflow tests")
    for t in a.list_tests("stack/"):
        a.report_test_start(t.name)
        check_exit_code_for_source(a, t.path)

    test_valid_progs(a)
    a.give_grade("3.2", 3)


def grade_use_after_free(args):
    a = Assignment(base_dir + "/assign3/tests/", args=args)
    a.rebuild_passes(base_dir + "/assign3/")

    a.start_test_section("Testing use-after-free tests")
    for t in a.list_tests("use-after-free/"):
        a.report_test_start(t.name)
        check_exit_code_for_source(a, t.path)

    test_valid_progs(a)
    a.give_grade("3.3", 3)
