
#include <stdio.h>
#include <stdlib.h>

static unsigned g2 = 5U;
static unsigned g3 = 3U;
static int g8 = 0;
int funct10() {
  int result = -2;
  printf("%d\n", 10);
  result = result * g8;
  printf("%d\n", g8);
  return result;
}
int funct9() {
  int result = funct10();
  result = result * g8;
  return result;
}
unsigned funct20() {
  unsigned result = 0U;
  result = result >> g3;
  printf("%x\n", g3);
  return result;
}

int main() {
  g2 = g3;

  unsigned x1 = 4 - 1;

  unsigned x2 = 2 % 1;
  printf("%x\n", 3U);
  unsigned x3 = 1 / 1;

  unsigned x4 = 5 % 2;
  g8 = funct9();
  g2 &= 6U;
  g2 -= funct20();

  x1 += 1 ^ x4;
  x2 ^= 1 * x3;
  x3 <<= 1 + x2;
  x4 ^= 1 / x1;
  x4 |= x1 + 1;
  x3 ^= x2 & 1;
  x2 <<= x3 << 1;
  x1 ^= x4 >> 0;
  x1 /= 1 + x4;
  x2 += 1 - x3;
  x3 -= 1 - x2;
  x4 >>= x1 << x1;
  x4 >>= x1 - 1;
  x3 >>= x2 % 1;
  x2 += x3 >> 1;
  x1 /= x4 % x3;
  printf("%x\n", 6U);
  printf("%x %x %x\n", x1, x2, x3);
}
