
#include <stdio.h>
#include <stdlib.h>

static unsigned g1 = 10U;
static unsigned g2 = 1U;
static unsigned g5 = 8U;
static int g17 = 6;
unsigned funct7() {
  unsigned result = 1U;
  printf("%x\n", g1);
  result = result + g1;
  return result;
}
unsigned funct4() {
  unsigned result = g5;
  printf("%x\n", funct7());
  result = result >> g2;
  printf("%d\n", 1);
  return result;
}
unsigned funct3() {
  unsigned result = funct4();
  printf("%x\n", 6U);
  result = result / g5;
  g17 = 2;
  return result;
}

unsigned calledInLoop(unsigned val) {
  unsigned result = val;
  printf("%d\n", 0);
  g17 += -8;
  g17 = 4;
  g17 *= 20;

  g17 = 6;
  g1 = g5;

  result += g1;
  g17 /= 10;
  g17 *= g17;

  g1 -= 1U;
  g17 = 1;

  return result;
}

int main() {
  unsigned n = 20U + 6U;
  unsigned a = 20U + 0;
  unsigned b = g2;
  unsigned c = 20U;
  unsigned d = funct3();
  (void)d;
  for (unsigned i = 0; i < n; i++) {
    unsigned x = calledInLoop(a);
    unsigned y = calledInLoop(b);
    unsigned z = calledInLoop(c);
    printf("%x %x %x\n", x, y, z);
  }
}
