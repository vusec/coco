
#include <stdio.h>
#include <stdlib.h>

static unsigned g1 = 1U;
static unsigned g7 = 2U;
static int g9 = 6;
unsigned funct5() {
  unsigned result = 10U;
  printf("%x\n", g7);
  result = result | 8U;
  g9 = 10;
  return result;
}
unsigned funct3() {
  unsigned result = 20U;
  printf("%x\n", 5U);
  result = result + funct5();
  return result;
}
unsigned funct2() {
  unsigned result = funct3();
  result = result << 0U;
  return result;
}

int main() {

  unsigned n = 20U + g1;
  printf("%x\n", g1);
  unsigned x = funct2();
  printf("%x\n", 6U);
  unsigned d = 2U;
  (void)d;
  printf("%x\n", 5U);
  unsigned f1 = funct5() * 1;
  printf("%x\n", g1);
  unsigned f2 = funct3();
  printf("%d\n", 4);
  for (unsigned i = 0; i < n; i++) {

    unsigned y = g1;
    printf("%x\n", 5U);
    unsigned z = g7;

    x = y + z;
    g7 /= g7;

    printf("%x\n", f1 * i + x * x);
    printf("%x\n", funct2());
    printf("%x\n", y * f2 + x);
    printf("%d\n", -2);
  }
}
