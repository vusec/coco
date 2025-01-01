
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g19 = 45;
int *gptr19 = &g19;
int f18() { return *gptr19; }
int f17() { return f18(); }

int main() {
  char x2[190] = {0};
  (void)x2;
  printf("Hello World\n");
  int *x = malloc(21);
  printf("Hello World\n");

  printf("%p\n", x);
  int i7 = 4;
  i7 += 8;
  printf("%d\n", i7);
  char x9[80] = {0};
  (void)x9;
  int *x11 = malloc(80);
  (void)x11;
  char x13[4] = {0};
  (void)x13;
  int i14 = 4;
  i14 += 8;
  printf("%d\n", i14);
  free(x11);
  printf("Hello World\n");
  char r19 = x9[f17()];
  (void)r19;
  free(x);

  printf("Hello World\n");
  x[2] = 4;
  printf("Hello World\n");
  printf("Hello World\n");
}