
#include <stdio.h>
#include <stdlib.h>

static unsigned g5 = 20U;
static int g7 = 10;
static int g8 = 4;
unsigned funct4() {
  unsigned result = g5;
  g7 ^= g8;
  g7 = 10;
  result = result / 10U;
  printf("%x\n", g5);
  return result;
}
unsigned funct2() {
  unsigned result = 0U;
  printf("%x\n", funct4());
  result = result / g5;
  printf("%x\n", 8U);
  return result;
}
unsigned funct1() {
  unsigned result = funct2();
  printf("%d\n", 1);
  result = result - 8U;
  printf("%d\n", 2);
  return result;
}

unsigned calledInLoop(unsigned val) {
  unsigned result = val;
  printf("%d\n", -2);
  printf("%d\n", 1);
  g5 -= 1U;
  g7 = g8;
  g7 &= -2;

  result += 2U;

  return result;
}

int main() {
  unsigned n = 20U + 8U;
  unsigned a = funct1() + 0;
  unsigned b = funct4();
  unsigned c = g5;
  unsigned d = g5;
  (void)d;
  for (unsigned i = 0; i < n; i++) {
    unsigned x = calledInLoop(a);
    unsigned y = calledInLoop(b);
    unsigned z = calledInLoop(c);
    printf("%x %x %x\n", x, y, z);
  }
}
