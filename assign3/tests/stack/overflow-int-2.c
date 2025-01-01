
#include <stdio.h>
#include <stdlib.h>

void other();
int main() {

  int i2 = 4;
  i2 += 8;
  printf("%d\n", i2);
  other();
}

void other() {

  int x[4] = {1};
  int i4 = 4;
  i4 += 4;
  printf("%d\n", i4);
  x[5] = 1;
  printf("Hello World\n");
  printf("%p\n", x);
  printf("Hello World\n");
}
