
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile int g10 = 2;
int f9() { return g10; }
int f13() { return 48; }
volatile int g15 = 1;
int f23() { return -4; }

int main() {
  int x2[80] = {0};
  (void)x2;
  char *x5 = malloc(4);
  (void)x5;
  int i7 = 4;
  i7 += 4;
  printf("%d\n", i7);
  char r10 = x5[f9()];
  (void)r10;
  printf("Hello World\n");
  free(x5);
  x2[f13()] = (int)g15;
  int *y = malloc(7);
  int x18[20] = {0};
  (void)x18;
  y[f23()] = 4;

  printf("%p\n", y);
  int i21 = 4;
  i21 += 1;
  printf("%d\n", i21);
  free(y);
  int i22 = 4;
  i22 += 1;
  printf("%d\n", i22);
}
