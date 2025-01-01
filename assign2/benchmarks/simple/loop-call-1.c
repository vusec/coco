
#include <stdio.h>
#include <stdlib.h>

static unsigned g4 = 20U;
static unsigned g8 = 2U;
static unsigned g10 = 20U;
static int g13 = -2;
unsigned funct3() {
  unsigned result = g4;
  result = result & 3U;
  return result;
}
unsigned funct7() {
  unsigned result = g8;
  result = result / g10;
  printf("%x\n", 3U);
  return result;
}
unsigned funct1() {
  unsigned result = 4U;
  printf("%x\n", funct3());
  result = result * funct7();
  g13 ^= g13;
  g8 &= 0U;
  g8 = g4;
  return result;
}

unsigned calledInLoop(unsigned val) {
  unsigned result = val;
  g4 >>= 4U;

  printf("%x\n", funct1());
  printf("%x\n", 20U);
  result += funct1();

  printf("%x\n", 5U);
  return result;
}

int main() {
  unsigned n = 20U + g8;
  unsigned a = funct1() + 0;
  unsigned b = g8;
  unsigned c = g8;
  unsigned d = g8;
  (void)d;
  for (unsigned i = 0; i < n; i++) {
    unsigned x = calledInLoop(a);
    unsigned y = calledInLoop(b);
    unsigned z = calledInLoop(c);
    printf("%x %x %x\n", x, y, z);
  }
}
