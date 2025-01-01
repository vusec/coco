
#include <stdio.h>
#include <stdlib.h>

volatile int g14 = 117;
volatile int *gptr14 = &g14;
int g15 = 4;
int *gptr15 = &g15;
volatile int g34 = 0;
int f33() { return g34; }
int f32() { return f33(); }
int g37 = 47;
int g38 = 4;
int *gptr38 = &g38;
int g41 = -2;
int *gptr41 = &g41;

void other();
int main() {

  printf("Hello World\n");
  other();
}

void other() {

  char y[4] = {1};
  int *x5 = malloc(320);
  (void)x5;
  int *x7 = malloc(320);
  (void)x7;
  int i8 = 4;
  i8 += 13;
  printf("%d\n", i8);
  free(x7);
  char *x10 = malloc(190);
  (void)x10;
  int i11 = 4;
  i11 += 1;
  printf("%d\n", i11);
  x10[*gptr14] = (char)*gptr15;
  int *x17 = malloc(320);
  (void)x17;
  int i18 = 4;
  i18 += 1;
  printf("%d\n", i18);
  printf("Hello World\n");
  x17[47] = (int)4;
  char x24[4] = {0};
  (void)x24;
  int x26[4] = {0};
  (void)x26;
  int i27 = 4;
  i27 += 4;
  printf("%d\n", i27);
  int x29[80] = {0};
  (void)x29;
  int r34 = x26[f32()];
  (void)r34;
  int i35 = 4;
  i35 += 1;
  printf("%d\n", i35);
  free(x17);
  free(x10);
  x5[g37] = (int)*gptr38;
  int i39 = 4;
  i39 += 8;
  printf("%d\n", i39);
  free(x5);

  y[*gptr41] = 4;

  printf("%p\n", y);
}
