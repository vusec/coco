#!/usr/bin/env bash

LLVM_FLAGS=$(llvm-config-14 --cxxflags --libfiles all)
SO_FLAGS=" -shared -fPIC -g -fsanitize=undefined -fno-sanitize-recover=all -Wno-missing-template-keyword"

set -e

g++ $LLVM_FLAGS $SO_FLAGS $1 -o $2