#!/bin/bash

cd "$(dirname "$0")"

LLVM_CONFIG="${LLVM_CONFIG:=llvm-config-14}"
CXX="${CXX:=g++}"
CC="${CC:=gcc}"
LLVM_FLAGS="$("${LLVM_CONFIG}" --cxxflags --libfiles all)"
SO_FLAGS=" -shared -fPIC "

set -e

"${CXX}" ${LLVM_FLAGS} ${SO_FLAGS} Instrument.cpp -o "${1}"
