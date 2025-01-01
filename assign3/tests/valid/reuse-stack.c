
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void first() {
    char c1[3] = {0};
    char c2[3] = {0};
    char c3[3] = {0};
    printf("%d\n", (int)c1[1]);
    printf("%d\n", (int)c2[2]);
    printf("%d\n", (int)c3[2]);
}
void second() {
    int buf[2] = {0};
    printf("%d\n", buf[1]);
}
int main() {
    first();
    second();
}