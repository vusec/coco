#include <stdio.h>

static int global1 = 3;

int main(int argc, char **argv) {
    int v = global1;
    int arg = argc + 1;
    for (int i = 0; i < 30; i++)
    {
        int z = arg + 10;
        int x = z * v + 4;
        int y = 4;
        printf("%d\n", i + x * y);
        printf("%d\n", y + x);
    }

    return 0;
}