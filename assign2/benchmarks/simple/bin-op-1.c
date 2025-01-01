
#include <stdio.h>
#include <stdlib.h>

static int g5 = 1;
static int g7 = -1;
static int g8 = -8;
static unsigned g14 = 8U;
int funct4() {
  int result = g5;
  printf("%d\n", g7);
  result = result - g8;
  return result;
}

int main() {

  unsigned x1 = 4 ^ 1;

  unsigned x2 = 2 - 1;
  printf("%d\n", funct4());
  unsigned x3 = 1 & 1;
  printf("%d\n", -8);
  unsigned x4 = 5 + 2;
  g8 /= g8;
  g14 = 4U;
  g14 = 2U;

  x1 &= 1 / x4;
  x2 *= 1 << x3;
  x3 -= 1 / x2;
  x4 &= 1 | x1;
  x4 |= x1 / 1;
  x3 %= x2 ^ 1;
  x2 ^= x3 ^ 1;
  x1 ^= x4 ^ 0;
  x1 *= 1 | x4;
  x2 -= 1 | x3;
  x3 &= 1 / x2;
  x4 ^= x1 | x1;
  x4 += x1 * 1;
  x3 ^= x2 & 1;
  x2 <<= x3 + 1;
  x1 &= x4 ^ x3;
  printf("%d\n", funct4());
  printf("%x %x %x\n", x1, x2, x3);
}
