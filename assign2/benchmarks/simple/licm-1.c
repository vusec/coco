#include <stdio.h>

static int global1 = 3;

int main(int argc, char **argv) {
    int v = global1;
    int arg = argc + 1;
    for (int i = 0; i < 40; i++)
    {
        int z = arg + 10;
        int x = z * v;
        int y = 4;
        printf("%d\n", i + x * x);
        printf("%d\n", i * y * 3 + x);
    }

    return 0;
}