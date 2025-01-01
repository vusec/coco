#include "stdio.h"

int other(int i, int j) {
    i += j;
    j -= 4;
    i += 2;
    return i;
}

int main() {
    int i = 0;
    i += other(i, i + 1);
    i += other(i, i + 2);
    i += other(i, i + 3);
    printf("Out: %d\n", other(i, i / 2));
}