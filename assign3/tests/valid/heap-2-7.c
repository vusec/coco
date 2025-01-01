
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f7() { return 0; }

int main() {
  int i1 = 4;
  i1 += 13;
  printf("%d\n", i1);
  printf("Hello World\n");
  unsigned size = 20;
  int *x = malloc(size);
  memset(x, 0, size);
  printf("Hello World\n");
  printf("Hello World\n");
  printf("%d\n", (int)x[f7()]);

  free(x);
  printf("Hello World\n");
}