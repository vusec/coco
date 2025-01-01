
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f11() { return 18; }

int *x;

int main() {
  char *x2 = malloc(190);
  (void)x2;
  printf("Hello World\n");
  free(x2);

  int *x5 = malloc(320);
  (void)x5;
  int i6 = 4;
  i6 += 13;
  printf("%d\n", i6);
  free(x5);

  unsigned size = f11();
  x = malloc(size);
  memset(x, 0, size);

  int i8 = 4;
  i8 += 1;
  printf("%d\n", i8);
  printf("%d\n", (int)x[2]);
  printf("Hello World\n");
  free(x);
  int i10 = 4;
  i10 += 1;
  printf("%d\n", i10);
}