#!/usr/bin/env python3
import os
import sys
import subprocess as sp
import json

# This script returns exit code 0 if the target program is most likely free
# of undefined behavior. Otherwise returns exit code 1.

src = sys.argv[1]

src_dir = os.path.dirname(os.path.realpath(__file__))
base_dir = os.path.realpath(os.path.join(src_dir, ".."))

use_msan = True

def get_clang_binary() -> str:
    config_file = os.path.join(base_dir, "framework", "config.json")

    with open(config_file, 'r') as file:
        config_json = json.load(file)
        return config_json["clang"]

src_dir = os.path.dirname(os.path.realpath(__file__))

clang = get_clang_binary()

tmp_file = "/tmp/bin-" + str(os.getpid())

inc_dirs = ["-I", "/usr/include/csmith/"]

error_flags = [
    "-Wall",
    "-Werror=format-insufficient-args",
    "-Werror=uninitialized",
    "-Werror=return-type",
    "-Werror=implicit-int",
    "-Werror=format-security",
    "-Werror=implicit-function-declaration",
    "-Wno-unused-variable",
    "-Wno-unused-function",
    "-Wno-unused-value",
    "-Wno-unused-but-set-variable",
    "-Wno-constant-logical-operand",
    "-Wno-int-conversion",
    "-Wno-unused-label",
    "-Wno-missing-braces",
    "-Wno-tautological-constant-out-of-range-compare",
    "-Wno-implicit-const-int-float-conversion"
]

flags = error_flags + inc_dirs

def remove_tmp():
    try:
        os.remove(tmp_file)
    except FileNotFoundError as e:
        pass

try:
    sp.check_call([clang, src, "-o", tmp_file, "-fsanitize=undefined,address", "-fno-sanitize-recover=undefined"] + flags)
    sp.check_call([tmp_file])
    # Not really needed as valgrind already takes care of all cases.
    if use_msan:
        sp.check_call([clang, src, "-o", tmp_file, "-fsanitize=memory", "-fno-sanitize-recover=memory"] + flags)
        sp.check_call([tmp_file])
    sp.check_call([clang, src, "-o", tmp_file] + flags)
    # This catches various other error such as uninitialzed memory use and so on.
    sp.check_call(["valgrind", "-q", tmp_file])
    remove_tmp()
except Exception as e:
    remove_tmp()
    print(e)
    sys.exit(1)
