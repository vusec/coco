#include <stdio.h>

static int global = 4;

int main() {
    global = 6;
    printf("%d\n", global);
}