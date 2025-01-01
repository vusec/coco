
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile int g15 = 71;
int f16() { return 1; }
int g21 = 40;
int *gptr21 = &g21;

int *x = 0;

int main() {
  printf("Hello World\n");
  printf("Hello World\n");
  x = malloc(*gptr21);

  printf("%p\n", x);
  int i5 = 4;
  i5 += 1;
  printf("%d\n", i5);

  free(x);
  printf("Hello World\n");
  char x9[80] = {0};
  (void)x9;
  int *x11 = malloc(320);
  (void)x11;
  int i12 = 4;
  i12 += 4;
  printf("%d\n", i12);
  free(x11);
  int i13 = 4;
  i13 += 4;
  printf("%d\n", i13);
  x9[g15] = (char)f16();
  printf("Hello World\n");
  x[3] = 4;
}