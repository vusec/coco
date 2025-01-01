
#include <stdio.h>
#include <stdlib.h>

static unsigned g2 = 1U;
static unsigned g4 = 6U;
static unsigned g6 = 0U;
static int g10 = -8;
unsigned funct1() {
  unsigned result = g2;
  result = result | g4;
  return result;
}
unsigned funct7() {
  unsigned result = g6;
  printf("%d\n", g10);
  result = result * funct1();
  return result;
}

unsigned calledInLoop(unsigned val) {
  unsigned result = val;
  printf("%x\n", 2U);
  g10 = -8;
  g6 = 1U;

  printf("%x\n", funct1());
  result += funct1();
  printf("%d\n", 6);
  g6 /= 20U;

  return result;
}

int main() {
  unsigned n = 20U + 3U;
  unsigned a = g6 + 0;
  unsigned b = 0U;
  unsigned c = funct7();
  unsigned d = funct1();
  (void)d;
  for (unsigned i = 0; i < n; i++) {
    unsigned x = calledInLoop(a);
    unsigned y = calledInLoop(b);
    unsigned z = calledInLoop(c);
    printf("%x %x %x\n", x, y, z);
  }
}
