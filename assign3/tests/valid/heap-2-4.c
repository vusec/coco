
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g9 = 1;

int main() {
  int i1 = 4;
  i1 += 4;
  printf("%d\n", i1);
  int x3[190] = {0};
  (void)x3;
  unsigned size = 20;
  int *x = malloc(size);
  memset(x, 0, size);
  printf("Hello World\n");

  printf("%d\n", (int)x[g9]);
  printf("Hello World\n");
  free(x);
}