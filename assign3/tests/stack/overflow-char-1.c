
#include <stdio.h>
#include <stdlib.h>

volatile int g11 = 2;
int f10() { return g11; }
int f14() { return 48; }
volatile int g16 = 1;
int f22() { return 7; }

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
  int x3[80] = {0};
  (void)x3;
  char *x6 = malloc(4);
  (void)x6;
  int i8 = 4;
  i8 += 4;
  printf("%d\n", i8);
  char r11 = x6[f10()];
  (void)r11;
  printf("Hello World\n");
  free(x6);
  x3[f14()] = (int)g16;
  y[f22()] = 4;
  int x19[20] = {0};
  (void)x19;
  printf("%p\n", y);
}
