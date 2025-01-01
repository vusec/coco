
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f8() { return 6; }

int main() {
  int *x2 = malloc(320);
  (void)x2;
  int i3 = 4;
  i3 += 13;
  printf("%d\n", i3);
  free(x2);

  int *x = malloc(4);

  x[f8()] = 1;
  int i5 = 4;
  i5 += 1;
  printf("%d\n", i5);
  printf("%p\n", x);
  printf("Hello World\n");
  free(x);
  int i7 = 4;
  i7 += 1;
  printf("%d\n", i7);
}
