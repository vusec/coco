#include "stdio.h"

int other() {
    int i = 2;
    return i + 2;
}

int main() {
    printf("Out: %d\n", other());
}