
#include <stdio.h>
#include <stdlib.h>

static int g5 = 6;
static unsigned g7 = 2U;
static int g9 = 4;
int funct4() {
  int result = g5;
  printf("%x\n", g7);
  result = result << 0;
  printf("%d\n", g9);
  return result;
}
int funct3() {
  int result = funct4();
  result = result - 4;
  return result;
}
int funct2() {
  int result = funct3();
  printf("%x\n", 0U);
  result = result >> funct3();
  printf("%x\n", g7);
  return result;
}

int main() {
  printf("%d\n", funct2());
  unsigned x1 = 4 + 1;
  printf("%x\n", 0U);
  unsigned x2 = 2 >> 1;
  g5 += 0;
  g5 >>= g5;
  g5 *= g5;

  unsigned x3 = 1 ^ 1;
  printf("%d\n", g9);
  unsigned x4 = 5 + 2;
  printf("%x\n", 20U);
  x1 -= 1 / x4;
  x2 <<= 1 >> x3;
  x3 &= 1 / x2;
  x4 %= 1 - x1;
  x4 %= x1 * 1;
  x3 /= x2 ^ 1;
  x2 <<= x3 << 1;
  x1 <<= x4 >> 0;
  x1 ^= 1 % x4;
  x2 -= 1 << x3;
  x3 -= 1 * x2;
  x4 |= x1 / x1;
  x4 >>= x1 / 1;
  x3 >>= x2 ^ 1;
  x2 |= x3 & 1;
  x1 += x4 - x3;
  printf("%x\n", 4U);
  printf("%x %x %x\n", x1, x2, x3);
}
