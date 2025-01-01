
#include <stdio.h>
#include <stdlib.h>

static unsigned g4 = 1U;
static unsigned g7 = 2U;
static unsigned g9 = 10U;
unsigned funct3() {
  unsigned result = g4;
  result = result & 8U;
  printf("%x\n", g7);
  return result;
}
unsigned funct8() {
  unsigned result = g9;
  printf("%x\n", 2U);
  result = result % 10U;
  g9 = g7;
  g9 /= g7;
  g4 ^= 1U;
  return result;
}
unsigned funct1() {
  unsigned result = 8U;
  printf("%x\n", funct3());
  result = result >> funct8();
  return result;
}

unsigned calledInLoop(unsigned val) {
  unsigned result = val;
  printf("%x\n", g4);
  printf("%x\n", 20U);
  printf("%d\n", 20);
  result += funct1();
  printf("%x\n", g7);

  return result;
}

int main() {
  unsigned n = 20U + 3U;
  unsigned a = 0U + 0;
  unsigned b = funct1();
  unsigned c = 3U;
  unsigned d = g4;
  (void)d;
  for (unsigned i = 0; i < n; i++) {
    unsigned x = calledInLoop(a);
    unsigned y = calledInLoop(b);
    unsigned z = calledInLoop(c);
    printf("%x %x %x\n", x, y, z);
  }
}
