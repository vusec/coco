
#include <stdio.h>
#include <stdlib.h>

volatile int g11 = 71;
int f12() { return 1; }

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
  int i1 = 4;
  i1 += 1;
  printf("%d\n", i1);
  char y[4] = {1};

  y[20] = 4;
  printf("Hello World\n");
  printf("%p\n", y);
  char x5[80] = {0};
  (void)x5;
  int *x7 = malloc(320);
  (void)x7;
  int i8 = 4;
  i8 += 4;
  printf("%d\n", i8);
  free(x7);
  int i9 = 4;
  i9 += 4;
  printf("%d\n", i9);
  x5[g11] = (char)f12();
  printf("Hello World\n");
}
