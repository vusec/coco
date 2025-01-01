
#include <stdio.h>
#include <stdlib.h>

static unsigned g5 = 5U;
static unsigned g6 = 2U;
static unsigned g7 = 4U;

int main() {

  unsigned x1 = 4 | 1;
  printf("%x\n", 0U);
  unsigned x2 = 2 | 1;

  unsigned x3 = 1 ^ 1;
  g5 = 20U;
  g6 = g7;

  unsigned x4 = 5 * 2;
  printf("%d\n", 1);
  x1 %= 1 << x4;
  x2 -= 1 + x3;
  x3 *= 1 | x2;
  x4 |= 1 | x1;
  x4 += x1 | 1;
  x3 ^= x2 / 1;
  x2 ^= x3 >> 1;
  x1 %= x4 ^ 0;
  x1 -= 1 & x4;
  x2 /= 1 - x3;
  x3 /= 1 >> x2;
  x4 <<= x1 % x1;
  x4 += x1 >> 1;
  x3 *= x2 >> 1;
  x2 ^= x3 * 1;
  x1 ^= x4 & x3;
  printf("%d\n", -2);
  printf("%x %x %x\n", x1, x2, x3);
}
