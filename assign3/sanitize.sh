#!/usr/bin/env bash

if [ "$#" -ne 2 ]; then
    echo "Invoke as: $0 INPUT.ll OUTPUT.ll"
    exit 77
fi

set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
INPUT="$1"
OUTPUT="$2"

# Fine the LLVM opt binary. The config.json has the path to it.
CONFIG_FILE="${SCRIPT_DIR}/../framework/config.json"
LLVM_OPT_BINARY=$(jq -r .opt ${CONFIG_FILE})

export OPT="${LLVM_OPT_BINARY} -load-pass-plugin=${SCRIPT_DIR}/Sanitizer.so -S "

$OPT -passes=coco-sanitizer "${INPUT}" -o "${OUTPUT}"
