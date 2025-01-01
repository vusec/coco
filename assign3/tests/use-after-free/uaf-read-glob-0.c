
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile int g16 = 3;
volatile int *gptr16 = &g16;
int f15() { return *gptr16; }
volatile int g17 = 1;
volatile int *gptr17 = &g17;
volatile int g33 = 2;
int f32() { return g33; }
int f36() { return 48; }
volatile int g38 = 1;
volatile int g40 = 2;
volatile int *gptr40 = &g40;

int *x = 0;

int main() {
  int x2[4] = {0};
  (void)x2;
  char *x5 = malloc(4);
  (void)x5;
  char *x7 = malloc(80);
  (void)x7;
  x7[57] = (char)1;
  printf("Hello World\n");
  free(x7);
  free(x5);
  x2[f15()] = (int)*gptr17;
  printf("Hello World\n");

  x = malloc(43);
  int i20 = 4;
  i20 += 13;
  printf("%d\n", i20);
  int i21 = 4;
  i21 += 13;
  printf("%d\n", i21);
  printf("%p\n", x);

  free(x);
  int x25[80] = {0};
  (void)x25;
  char *x28 = malloc(4);
  (void)x28;
  int i30 = 4;
  i30 += 4;
  printf("%d\n", i30);
  char r33 = x28[f32()];
  (void)r33;
  printf("Hello World\n");
  free(x28);
  x25[f36()] = (int)g38;

  printf("%d\n", (int)x[*gptr40]);
}