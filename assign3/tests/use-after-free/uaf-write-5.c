
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g14 = 0;

int main() {
  char x2[20] = {0};
  (void)x2;
  int *x5 = malloc(16);
  (void)x5;
  int i6 = 4;
  i6 += 4;
  printf("%d\n", i6);
  free(x5);

  int *x = malloc(16);
  printf("Hello World\n");
  printf("Hello World\n");
  printf("%p\n", x);
  char *x10 = malloc(4);
  (void)x10;
  int i11 = 4;
  i11 += 4;
  printf("%d\n", i11);
  int i12 = 4;
  i12 += 4;
  printf("%d\n", i12);
  char r14 = x10[g14];
  (void)r14;
  free(x10);

  free(x);
  int i17 = 4;
  i17 += 8;
  printf("%d\n", i17);
  printf("Hello World\n");
  x[2] = 4;
  int i19 = 4;
  i19 += 4;
  printf("%d\n", i19);
  printf("Hello World\n");
}