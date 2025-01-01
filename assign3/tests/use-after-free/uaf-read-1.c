
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g14 = 3;
int *gptr14 = &g14;
volatile int g23 = 4;
volatile int *gptr23 = &g23;
int f22() { return *gptr23; }
int f21() { return f22(); }
volatile int g30 = 104;
volatile int *gptr30 = &g30;

int main() {
  int i1 = 4;
  i1 += 13;
  printf("%d\n", i1);

  int *x = malloc(*gptr30);
  int *x4 = malloc(16);
  (void)x4;
  int i5 = 4;
  i5 += 1;
  printf("%d\n", i5);
  free(x4);

  printf("%p\n", x);
  int *x8 = malloc(760);
  (void)x8;
  int *x10 = malloc(16);
  (void)x10;
  printf("Hello World\n");
  int r14 = x10[*gptr14];
  (void)r14;
  int i15 = 4;
  i15 += 8;
  printf("%d\n", i15);
  free(x10);
  int *x17 = malloc(16);
  (void)x17;
  free(x17);
  x8[171] = (int)f21();
  printf("Hello World\n");
  free(x8);

  printf("Hello World\n");
  free(x);

  printf("Hello World\n");
  printf("%d\n", (int)x[1]);

  printf("Hello World\n");
}