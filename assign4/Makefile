.PHONY : all
GENERATED_FILES = ExampleBrokenPass.so GVN.so GVN.original.so GlobalOpt.so GlobalOpt.original.so InstSimplify.so InstSimplify.original.so
all : $(GENERATED_FILES)
COMPILE="../framework/utils/compile-pass.sh"

ExampleBrokenPass.so: ExampleBrokenPass.cpp
	${COMPILE} ExampleBrokenPass.cpp ExampleBrokenPass.so

# InstSimplify
InstSimplify.so: InstSimplify.cpp
	${COMPILE} InstSimplify.cpp InstSimplify.so

InstSimplify.original.so: original-src/InstSimplify.cpp
	${COMPILE} original-src/InstSimplify.cpp InstSimplify.original.so

# FlattenCFG
GVN.so: GVN.cpp
	${COMPILE} GVN.cpp GVN.so

GVN.original.so: original-src/GVN.cpp
	${COMPILE} original-src/GVN.cpp GVN.original.so

# GlobalOpt
GlobalOpt.so: GlobalOpt.cpp
	${COMPILE} GlobalOpt.cpp GlobalOpt.so

GlobalOpt.original.so: original-src/GlobalOpt.cpp
	${COMPILE} original-src/GlobalOpt.cpp GlobalOpt.original.so

clean:
	rm -f $(GENERATED_FILES)