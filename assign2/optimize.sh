#!/bin/bash

# Note for students: You can skip to the end of this file for the actual
# optimization pass pipeline. The code inbetween is just boilerplate
# for running/loading the passes.

if [ "$#" -ne 2 ]; then
    echo "Invoke as: $0 INPUT.ll OUTPUT.ll"
    exit 77
fi


set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
TEST_NAME=$(basename $1)
TMP_DIR="${SCRIPT_DIR}/opt-tmp/${TEST_NAME}/"
INPUT="$1"
OUTPUT="$2"

# Fine the LLVM opt binary. The config.json has the path to it.
CONFIG_FILE="${SCRIPT_DIR}/../framework/config.json"
LLVM_OPT_BINARY=$(jq -r .opt ${CONFIG_FILE})

mkdir -p "${TMP_DIR}"

export OPT="${LLVM_OPT_BINARY} -load-pass-plugin=${SCRIPT_DIR}/Inlining.so -load-pass-plugin=${SCRIPT_DIR}/InstCombine.so  -load-pass-plugin=${SCRIPT_DIR}/LICM.so  -load-pass-plugin=${SCRIPT_DIR}/ADCE.so -S "

LAST_OUTPUT="${INPUT}"
FILE_INDEX="0"
run_pass () {
  FILE_INDEX=$((FILE_INDEX + 1))
  NEXT_OUTPUT="${TMP_DIR}/${FILE_INDEX}.${1}.ll"
  $OPT "-passes=${1}" "${LAST_OUTPUT}" -o "${NEXT_OUTPUT}" 
  LAST_OUTPUT="${NEXT_OUTPUT}"
}

# Student note: Compilation pipeline starts here. Passes are run in the order
# specified below.
run_pass coco-licm
run_pass coco-adce
run_pass coco-instcombine
run_pass coco-inliner

cp "${LAST_OUTPUT}" "${OUTPUT}"