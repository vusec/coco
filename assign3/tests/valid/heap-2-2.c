
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  int i2 = 4;
  i2 += 8;
  printf("%d\n", i2);
  unsigned size = 20;
  int *x = malloc(size);
  memset(x, 0, size);

  int i4 = 4;
  i4 += 4;
  printf("%d\n", i4);
  printf("%d\n", (int)x[2]);
  printf("Hello World\n");
  free(x);
  printf("Hello World\n");
}