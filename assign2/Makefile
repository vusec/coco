.PHONY : all
all : Inlining.so LICM.so InstCombine.so ADCE.so
COMPILE="../framework/utils/compile-pass.sh"

ADCE.so: ADCE.cpp
	${COMPILE} ADCE.cpp ADCE.so

Inlining.so: Inlining.cpp
	${COMPILE} Inlining.cpp Inlining.so

LICM.so: LICM.cpp
	${COMPILE} LICM.cpp LICM.so

InstCombine.so: InstCombine.cpp
	${COMPILE} InstCombine.cpp InstCombine.so
