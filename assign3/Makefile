.PHONY : all
all : Sanitizer.so Runtime.so
COMPILE="../framework/utils/compile-pass.sh"

Sanitizer.so: Sanitizer.cpp
	${COMPILE} Sanitizer.cpp Sanitizer.so

Runtime.so: Runtime.cpp
	clang++ -fPIC -std=c++17 Runtime.cpp -o Runtime.so -shared -g

