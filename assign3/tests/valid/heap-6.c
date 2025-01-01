
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *x;

int main() {
  int i1 = 4;
  i1 += 1;
  printf("%d\n", i1);
  char x3[80] = {0};
  (void)x3;
  printf("Hello World\n");
  unsigned size = 17;
  x = malloc(size);
  memset(x, 0, size);
  printf("Hello World\n");

  printf("%d\n", (int)x[2]);

  free(x);
  int i8 = 4;
  i8 += 1;
  printf("%d\n", i8);
}