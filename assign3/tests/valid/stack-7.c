
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f7() { return 0; }

void other();
int main() {
  int i1 = 4;
  i1 += 13;
  printf("%d\n", i1);
  printf("Hello World\n");
  other();
}

void other() {
  printf("Hello World\n");
  int x[4] = {1};
  printf("Hello World\n");
  x[f7()] = 1;

  printf("%d\n", (int)x[0]);
  printf("Hello World\n");
}