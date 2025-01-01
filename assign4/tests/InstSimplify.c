#include <stdio.h>
int global = 4;
int main() {
    global ^= 0;
    printf("%d\n", global);
}