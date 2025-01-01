
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g15 = 178;

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

  int *x = malloc(g15);

  int i8 = 4;
  i8 += 1;
  printf("%d\n", i8);
  printf("%p\n", x);
  printf("Hello World\n");
  int i10 = 4;
  i10 += 1;
  printf("%d\n", i10);
  free(x);
  int i11 = 4;
  i11 += 13;
  printf("%d\n", i11);

  printf("%d\n", (int)x[1]);
  int i13 = 4;
  i13 += 13;
  printf("%d\n", i13);
  printf("Hello World\n");
}