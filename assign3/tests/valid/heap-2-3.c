
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int i1 = 4;
  i1 += 1;
  printf("%d\n", i1);
  printf("Hello World\n");
  unsigned size = 20;
  int *x = malloc(size);
  memset(x, 0, size);
  int i3 = 4;
  i3 += 8;
  printf("%d\n", i3);
  printf("Hello World\n");
  printf("%d\n", (int)x[1]);

  free(x);
  int i6 = 4;
  i6 += 4;
  printf("%d\n", i6);
}