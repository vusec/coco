
#include <stdio.h>
#include <stdlib.h>

int g10 = 29;
int *gptr10 = &g10;
int f9() { return *gptr10; }

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
  char x3[190] = {0};
  (void)x3;
  y[f9()] = 4;
  int *x6 = malloc(320);
  (void)x6;
  int i7 = 4;
  i7 += 13;
  printf("%d\n", i7);
  free(x6);

  printf("%p\n", y);
  int i8 = 4;
  i8 += 1;
  printf("%d\n", i8);
}
