
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g9 = 5;
int *gptr9 = &g9;
int f8() { return *gptr9; }

int main() {
  int i1 = 4;
  i1 += 1;
  printf("%d\n", i1);
  int *x = malloc(4);
  char x3[80] = {0};
  (void)x3;
  printf("Hello World\n");
  x[f8()] = 1;
  printf("Hello World\n");
  printf("%p\n", x);

  free(x);
}
