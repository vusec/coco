
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g6 = 3;

int main() {

  int *y = malloc(4);

  y[g6] = 4;
  int i3 = 4;
  i3 += 8;
  printf("%d\n", i3);
  printf("%p\n", y);
  printf("Hello World\n");
  free(y);
  int i5 = 4;
  i5 += 4;
  printf("%d\n", i5);
}
