
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

  char y[4] = {1};
  int i4 = 4;
  i4 += 4;
  printf("%d\n", i4);
  y[-4] = 4;
  printf("Hello World\n");
  printf("%p\n", y);
  printf("Hello World\n");
}
