
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void other();
int main() {
  int i1 = 4;
  i1 += 1;
  printf("%d\n", i1);
  printf("Hello World\n");
  other();
}

void other() {
  int i3 = 4;
  i3 += 8;
  printf("%d\n", i3);
  int x[4] = {1};
  printf("Hello World\n");
  x[1] = 1;

  printf("%d\n", (int)x[0]);
  int i6 = 4;
  i6 += 4;
  printf("%d\n", i6);
}