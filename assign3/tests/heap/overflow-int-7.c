
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g6 = 6;

int main() {

  int *x = malloc(4);

  x[g6] = 1;
  int i3 = 4;
  i3 += 8;
  printf("%d\n", i3);
  printf("%p\n", x);
  printf("Hello World\n");
  free(x);
  int i5 = 4;
  i5 += 4;
  printf("%d\n", i5);
}
