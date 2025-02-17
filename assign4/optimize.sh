#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Invoke as: $0 INPUT.ll OUTPUT PassName"
    echo " Possible passes are: ExampleBrokenPass GlobalOpt GVN InstSimplify"
    echo " ('None' as a pass name runs without optimizations)"
    exit 77
fi

set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
INPUT="$1"
OUTPUT="$2"
PASS="$3"

# Delete the output, This avoids that we run tests with a stale IR file from
# a previous run.
rm -f "${OUTPUT}"

# Remove the '.original' from the pass name.
PASS_NAME="${PASS/.original/}"

LL_FILE="${OUTPUT}.preopt.ll"
OPT_FILE="${OUTPUT}.opt.ll"
MEM2REG_FILE="${OUTPUT}.mem2reg.ll"

# Fine the LLVM opt binary. The config.json has the path to it.
CONFIG_FILE="${SCRIPT_DIR}/../framework/config.json"
LLVM_OPT_BINARY=$(jq -r .opt ${CONFIG_FILE})
CLANG_BINARY=$(jq -r .clang ${CONFIG_FILE})

"${CLANG_BINARY}" "${INPUT}" -o "${LL_FILE}" -S -emit-llvm -Xclang -disable-O0-optnone -I /usr/include/csmith/ -Wno-everything

if [ "$PASS" = "None" ]; then
    "${CLANG_BINARY}" "${LL_FILE}" -o "${OUTPUT}"
    exit 0
fi

OPT="${LLVM_OPT_BINARY} -load-pass-plugin=${SCRIPT_DIR}/${PASS}.so -S "
${OPT} "-passes=mem2reg" "${LL_FILE}" -o "${MEM2REG_FILE}"
${OPT} "-passes=${PASS_NAME}" "${MEM2REG_FILE}" -o "${OPT_FILE}"
"${CLANG_BINARY}" "${OPT_FILE}" -o "${OUTPUT}"