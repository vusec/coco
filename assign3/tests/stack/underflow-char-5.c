
#include <stdio.h>
#include <stdlib.h>

int f11() { return -1; }

void other();
int main() {
  char *x2 = malloc(190);
  (void)x2;
  printf("Hello World\n");
  free(x2);

  int *x5 = malloc(320);
  (void)x5;
  int i6 = 4;
  i6 += 13;
  printf("%d\n", i6);
  free(x5);

  other();
}

void other() {

  char y[4] = {1};
  int i8 = 4;
  i8 += 1;
  printf("%d\n", i8);
  y[f11()] = 4;
  printf("Hello World\n");
  printf("%p\n", y);
  int i10 = 4;
  i10 += 1;
  printf("%d\n", i10);
}
