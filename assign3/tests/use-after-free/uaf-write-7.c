
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g11 = 99;
int *gptr11 = &g11;
int f12() { return 1; }
int g29 = 1;

int main() {

  int x3[4] = {0};
  (void)x3;
  int *x5 = malloc(760);
  (void)x5;
  char *x8 = malloc(190);
  (void)x8;
  free(x8);
  x5[*gptr11] = (int)f12();
  printf("Hello World\n");
  free(x5);

  int *x = malloc(17);
  int i15 = 4;
  i15 += 1;
  printf("%d\n", i15);

  printf("%p\n", x);
  int *x18 = malloc(760);
  (void)x18;
  free(x18);

  int i20 = 4;
  i20 += 1;
  printf("%d\n", i20);
  free(x);

  char x23[20] = {0};
  (void)x23;
  int *x25 = malloc(80);
  (void)x25;
  int i26 = 4;
  i26 += 4;
  printf("%d\n", i26);
  free(x25);
  printf("Hello World\n");
  char r29 = x23[g29];
  (void)r29;
  printf("Hello World\n");
  x[2] = 4;
  int i31 = 4;
  i31 += 13;
  printf("%d\n", i31);
}