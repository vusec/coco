
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g10 = 99;
int *gptr10 = &g10;
int f11() { return 1; }
int g28 = 1;

int *x = 0;

int main() {
  int x2[4] = {0};
  (void)x2;
  int *x4 = malloc(760);
  (void)x4;
  char *x7 = malloc(190);
  (void)x7;
  free(x7);
  x4[*gptr10] = (int)f11();
  printf("Hello World\n");
  free(x4);

  int i14 = 4;
  i14 += 1;
  printf("%d\n", i14);
  x = malloc(40);

  int *x17 = malloc(760);
  (void)x17;
  free(x17);

  printf("%p\n", x);
  int i19 = 4;
  i19 += 1;
  printf("%d\n", i19);

  free(x);
  char x22[20] = {0};
  (void)x22;
  int *x24 = malloc(80);
  (void)x24;
  int i25 = 4;
  i25 += 4;
  printf("%d\n", i25);
  free(x24);
  printf("Hello World\n");
  char r28 = x22[g28];
  (void)r28;
  printf("Hello World\n");
  int i30 = 4;
  i30 += 13;
  printf("%d\n", i30);
  x[3] = 4;
}