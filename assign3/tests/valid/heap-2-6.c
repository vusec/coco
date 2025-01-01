
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int *x2 = malloc(320);
  (void)x2;
  int i3 = 4;
  i3 += 13;
  printf("%d\n", i3);
  free(x2);

  unsigned size = 20;
  int *x = malloc(size);
  memset(x, 0, size);
  int i5 = 4;
  i5 += 1;
  printf("%d\n", i5);
  printf("Hello World\n");
  printf("%d\n", (int)x[0]);
  int i7 = 4;
  i7 += 1;
  printf("%d\n", i7);
  free(x);
  int i8 = 4;
  i8 += 13;
  printf("%d\n", i8);
}