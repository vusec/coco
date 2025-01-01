
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void other();
int main() {
  int i1 = 4;
  i1 += 1;
  printf("%d\n", i1);
  char x3[80] = {0};
  (void)x3;
  printf("Hello World\n");
  other();
}

void other() {
  printf("Hello World\n");
  int x[6] = {1};

  x[2] = 1;

  printf("%d\n", (int)x[0]);
  int i8 = 4;
  i8 += 1;
  printf("%d\n", i8);
}