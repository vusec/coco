
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void other();
int main() {

  int i2 = 4;
  i2 += 8;
  printf("%d\n", i2);
  other();
}

void other() {

  int x[6] = {1};
  int i4 = 4;
  i4 += 4;
  printf("%d\n", i4);
  x[0] = 1;
  printf("Hello World\n");
  printf("%d\n", (int)x[0]);
  printf("Hello World\n");
}