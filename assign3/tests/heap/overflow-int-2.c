
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g8 = 3;
int *gptr8 = &g8;
volatile int g17 = 4;
volatile int *gptr17 = &g17;
int f16() { return *gptr17; }
int f15() { return f16(); }
int g23 = 6;

int main() {
  int *x2 = malloc(760);
  (void)x2;
  int *x4 = malloc(16);
  (void)x4;
  printf("Hello World\n");
  int r8 = x4[*gptr8];
  (void)r8;
  int i9 = 4;
  i9 += 8;
  printf("%d\n", i9);
  free(x4);
  int *x11 = malloc(16);
  (void)x11;
  free(x11);
  x2[171] = (int)f15();
  printf("Hello World\n");
  free(x2);

  int *x = malloc(4);
  printf("Hello World\n");
  x[g23] = 1;

  printf("%p\n", x);
  printf("Hello World\n");
  free(x);
}
