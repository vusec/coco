
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile int g7 = 3;
volatile int g16 = 1;
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

  int x[6] = {1};
  printf("Hello World\n");
  x[*gptr16] = 1;

  printf("%d\n", (int)x[0]);
  printf("Hello World\n");
}