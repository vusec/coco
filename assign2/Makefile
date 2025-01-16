.PHONY : all
all : Inlining.so LICM.so InstCombine.so ADCE.so
COMPILE="../framework/utils/compile-pass.sh"

CC ?= gcc
CXX ?= g++
LLVM_CONFIG ?= llvm-config-14

export CC CXX LLVM_CONFIG

clean:
	rm *.so

ADCE.so: ADCE.cpp
	${COMPILE} ADCE.cpp ADCE.so

Inlining.so: Inlining.cpp
	${COMPILE} Inlining.cpp Inlining.so

LICM.so: LICM.cpp
	${COMPILE} LICM.cpp LICM.so

InstCombine.so: InstCombine.cpp
	${COMPILE} InstCombine.cpp InstCombine.so
