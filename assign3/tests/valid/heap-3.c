
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile int g7 = 3;
volatile int g16 = 15;
volatile int *gptr16 = &g16;

int *x;

int main() {
  int x2[80] = {0};
  (void)x2;
  printf("Hello World\n");
  printf("Hello World\n");
  x2[55] = (int)g7;
  int x9[190] = {0};
  (void)x9;
  printf("Hello World\n");
  unsigned size = *gptr16;
  x = malloc(size);
  memset(x, 0, size);

  printf("Hello World\n");
  printf("%d\n", (int)x[2]);

  free(x);
  printf("Hello World\n");
}