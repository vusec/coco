
#include <stdio.h>
#include <stdlib.h>

int g10 = 3;
int *gptr10 = &g10;
volatile int g19 = 4;
volatile int *gptr19 = &g19;
int f18() { return *gptr19; }
int f17() { return f18(); }

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

  char y[4] = {1};

  y[15] = 4;
  int *x4 = malloc(760);
  (void)x4;
  int *x6 = malloc(16);
  (void)x6;
  printf("Hello World\n");
  int r10 = x6[*gptr10];
  (void)r10;
  int i11 = 4;
  i11 += 8;
  printf("%d\n", i11);
  free(x6);
  int *x13 = malloc(16);
  (void)x13;
  free(x13);
  x4[171] = (int)f17();
  printf("Hello World\n");
  free(x4);

  printf("%p\n", y);
  printf("Hello World\n");
}
