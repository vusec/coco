#!/usr/bin/env bash

cd "$(dirname "$0")"

LLVM_FLAGS=$(llvm-config-14 --cxxflags --libfiles all)
SO_FLAGS=" -shared -fPIC "

set -e

g++ $LLVM_FLAGS $SO_FLAGS Instrument.cpp -o $1
