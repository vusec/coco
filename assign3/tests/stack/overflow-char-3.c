
#include <stdio.h>
#include <stdlib.h>

void other();
int main() {
  char x1[2] = {2};
  printf("%p\n", x1);
  char x2[2] = {2};
  printf("%p\n", x2);
  char x3[2] = {2};
  printf("%p\n", x3);
  char x4[2] = {2};
  printf("%p\n", x4);
  other();
}

void other() {
  printf("Hello World\n");
  char y[4] = {1};

  y[29] = 4;
  printf("Hello World\n");
  printf("%p\n", y);
  char x5[20] = {0};
  (void)x5;
  printf("Hello World\n");
}
