
#include <stdio.h>
#include <stdlib.h>

volatile int g11 = 117;
volatile int *gptr11 = &g11;
int g12 = 4;
int *gptr12 = &g12;
volatile int g31 = 0;
int f30() { return g31; }
int f29() { return f30(); }
int g34 = 47;
int g35 = 4;
int *gptr35 = &g35;

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
  int *x2 = malloc(320);
  (void)x2;
  int *x4 = malloc(320);
  (void)x4;
  int i5 = 4;
  i5 += 13;
  printf("%d\n", i5);
  free(x4);
  char *x7 = malloc(190);
  (void)x7;
  int i8 = 4;
  i8 += 1;
  printf("%d\n", i8);
  x7[*gptr11] = (char)*gptr12;
  int *x14 = malloc(320);
  (void)x14;
  int i15 = 4;
  i15 += 1;
  printf("%d\n", i15);
  printf("Hello World\n");
  x14[47] = (int)4;
  char x21[4] = {0};
  (void)x21;
  int x23[4] = {0};
  (void)x23;
  int i24 = 4;
  i24 += 4;
  printf("%d\n", i24);
  int x26[80] = {0};
  (void)x26;
  int r31 = x23[f29()];
  (void)r31;
  int i32 = 4;
  i32 += 1;
  printf("%d\n", i32);
  free(x14);
  free(x7);
  x2[g34] = (int)*gptr35;
  int i36 = 4;
  i36 += 8;
  printf("%d\n", i36);
  free(x2);

  char y[4] = {1};

  y[11] = 4;
  int x39[80] = {0};
  (void)x39;
  printf("%p\n", y);
  printf("Hello World\n");
}
