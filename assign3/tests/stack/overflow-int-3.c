
#include <stdio.h>
#include <stdlib.h>

volatile int g7 = 3;
volatile int g16 = 5;
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

  int x[4] = {1};
  printf("Hello World\n");
  x[*gptr16] = 1;

  printf("%p\n", x);
  printf("Hello World\n");
}
