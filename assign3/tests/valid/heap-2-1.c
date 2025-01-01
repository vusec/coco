
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile int g9 = 2;
int f8() { return g9; }
volatile int g13 = 2;
volatile int g22 = 0;
volatile int *gptr22 = &g22;

int main() {
  int *x2 = malloc(760);
  (void)x2;
  char *x4 = malloc(4);
  (void)x4;
  int i6 = 4;
  i6 += 4;
  printf("%d\n", i6);
  char r9 = x4[f8()];
  (void)r9;
  printf("Hello World\n");
  free(x4);
  int i11 = 4;
  i11 += 13;
  printf("%d\n", i11);
  int r13 = x2[g13];
  (void)r13;
  free(x2);

  int x16[20] = {0};
  (void)x16;
  unsigned size = 20;
  int *x = malloc(size);
  memset(x, 0, size);

  int i19 = 4;
  i19 += 1;
  printf("%d\n", i19);
  printf("%d\n", (int)x[*gptr22]);
  int i20 = 4;
  i20 += 1;
  printf("%d\n", i20);
  free(x);
  int i21 = 4;
  i21 += 1;
  printf("%d\n", i21);
}