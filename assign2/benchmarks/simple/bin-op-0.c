
#include <stdio.h>
#include <stdlib.h>

static int g4 = -2;
static unsigned g8 = 20U;
static int g12 = -8;
int funct13() {
  int result = g4;
  g4 = 4;
  result = result - 4;
  g8 <<= 20U;
  return result;
}
unsigned funct10() {
  unsigned result = 1U;
  g12 = funct13();
  g4 ^= 20;
  result = result | g8;
  printf("%x\n", 2U);
  return result;
}
unsigned funct9() {
  unsigned result = funct10();
  printf("%x\n", funct10());
  result = result + 3U;
  g8 = 20U;
  return result;
}

int main() {

  unsigned x1 = 4 - 1;

  unsigned x2 = 2 % 1;
  printf("%d\n", g4);
  unsigned x3 = 1 % 1;
  printf("%x\n", 20U);
  unsigned x4 = 5 << 2;

  x1 ^= 1 << x4;
  x2 += 1 << x3;
  x3 /= 1 | x2;
  x4 -= 1 >> (x1 / 8202 - 122);
  x4 *= x1 / 1;
  x3 >>= x2 / 200;
  x2 *= x3 * 1;
  x1 ^= x4 + 0;
  x1 += 1 / x4;
  x2 ^= 1 % (x3 + 1);
  x3 -= 1 + x2;
  x4 %= x1 / x1;
  x4 ^= x1 >> 1;
  x3 *= x2 + 1;
  x2 -= x3 % 1;
  x1 &= x4 / x3;
  g8 = funct9();
  g12 = g12;
  g8 ^= funct10();

  printf("%x %x %x %x\n", x1, x2, x3, g8);
}
