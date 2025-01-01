#include <stdio.h>

static int global1 = 3;

int funct31(int i) {
    return i + i;
}

int funct20(int i) {
    return i + 10;
}

int main(int argc, char **argv) {
    int v = global1;
    int arg = argc + 1;
    for (int i = 0; i < 40; i++)
    {
        int z = arg + funct20(arg);
        int x = z * v + funct31(v);
        int y = funct20(z);
        printf("%d\n", i + x * x);
        printf("%d\n", i * y * 3 + x);
    }

    return 0;
}