
#include <stdio.h>
#include <stdlib.h>

static unsigned g1 = 4U;
static unsigned g5 = 10U;
static unsigned g7 = 1U;
static int g9 = 2;
unsigned funct4() {
  unsigned result = g5;
  printf("%x\n", 2U);
  result = result ^ g7;
  g9 ^= 10;
  g1 /= 3U;
  return result;
}
unsigned funct3() {
  unsigned result = funct4();
  result = result ^ 2U;
  printf("%x\n", 1U);
  return result;
}
unsigned funct2() {
  unsigned result = funct3();
  result = result - g1;
  printf("%x\n", funct3());
  return result;
}

int main() {
  printf("%x\n", 20U);
  unsigned n = 20U + g1;
  printf("%x\n", 2U);
  unsigned x = 6U;
  g5 %= 20U;

  unsigned d = 20U;
  (void)d;
  printf("%x\n", g7);
  unsigned f1 = funct2() * 1;
  printf("%d\n", 6);
  unsigned f2 = funct2();
  printf("%x\n", 5U);
  for (unsigned i = 0; i < n; i++) {
    g9 = 4;
    g9 = 4;
    g9 = 6;

    unsigned y = g1;
    printf("%x\n", g1);
    unsigned z = 5U;

    x = y + z;
    printf("%x\n", funct4());
    printf("%x\n", f1 * i + x * x);
    printf("%x\n", 4U);
    printf("%x\n", y * f2 + x);
    g5 += 5U;
    g1 = g7;
    g9 = -2;
  }
}
