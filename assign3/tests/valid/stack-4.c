
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g9 = 1;

void other();
int main() {
  int i1 = 4;
  i1 += 4;
  printf("%d\n", i1);
  int x3[190] = {0};
  (void)x3;
  other();
}

void other() {
  printf("Hello World\n");
  int x[4] = {1};

  x[g9] = 1;
  printf("Hello World\n");
  printf("%d\n", (int)x[0]);
}