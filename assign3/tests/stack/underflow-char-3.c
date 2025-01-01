
#include <stdio.h>
#include <stdlib.h>

volatile int g7 = 3;
volatile int g16 = -3;
volatile int *gptr16 = &g16;

void other();
int main() {
  int x2[80] = {0};
  (void)x2;
  printf("Hello World\n");
  printf("Hello World\n");
  x2[55] = (int)g7;
  int x9[190] = {0};
  (void)x9;
  printf("Hello World\n");
  other();
}

void other() {

  char y[4] = {1};
  printf("Hello World\n");
  y[*gptr16] = 4;

  printf("%p\n", y);
  printf("Hello World\n");
}
