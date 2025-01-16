#include <stdio.h>
int main() {
    int i; // uninit use, which leads to nondeterministic behavior.
    printf("%d\n", i);
}