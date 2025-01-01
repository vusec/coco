
#include <stdio.h>
#include <stdlib.h>

int f5() { return 7; }

void other();
int main() {
  char x1[2] = {2};
  printf("%p\n", x1);
  char x2[2] = {2};
  printf("%p\n", x2);
  char x3[2] = {2};
  printf("%p\n", x3);
  char x4[2] = {2};
  printf("%p\n", x4);
  other();
}

void other() {
  printf("Hello World\n");
  char y[4] = {1};
  printf("Hello World\n");
  y[f5()] = 4;

  printf("%p\n", y);
  printf("Hello World\n");
}
