
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void other();
int main() {
  int *x2 = malloc(320);
  (void)x2;
  int i3 = 4;
  i3 += 13;
  printf("%d\n", i3);
  free(x2);

  other();
}

void other() {
  int i5 = 4;
  i5 += 1;
  printf("%d\n", i5);
  int x[4] = {1};
  printf("Hello World\n");
  x[0] = 1;
  int i7 = 4;
  i7 += 1;
  printf("%d\n", i7);
  printf("%d\n", (int)x[0]);
  int i8 = 4;
  i8 += 13;
  printf("%d\n", i8);
}