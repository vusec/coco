#!/bin/bash

LLVM_CONFIG="${LLVM_CONFIG:=llvm-config-14}"
CXX="${CXX:=g++}"
CC="${CC:=gcc}"
LLVM_FLAGS="$("${LLVM_CONFIG}" --cxxflags --libfiles all)"
SO_FLAGS=" -shared -fPIC -g -fsanitize=undefined -fno-sanitize-recover=all -Wno-missing-template-keyword"

set -e

"${CXX}" ${LLVM_FLAGS} ${SO_FLAGS} "${1}" -o "${2}"
