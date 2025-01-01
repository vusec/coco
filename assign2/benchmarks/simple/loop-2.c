
#include <stdio.h>
#include <stdlib.h>

static unsigned g1 = 5U;
static unsigned g4 = 3U;
static unsigned g10 = 4U;
static int g15 = -1;
int funct7() {
  int result = -2;
  printf("%d\n", 4);
  result = result & -1;
  return result;
}
unsigned funct5() {
  unsigned result = 20U;
  printf("%d\n", funct7());
  result = result & g10;
  printf("%x\n", 6U);
  return result;
}
unsigned funct2() {
  unsigned result = 20U;
  printf("%x\n", g4);
  result = result ^ funct5();
  printf("%x\n", 0U);
  return result;
}

int main() {
  printf("%d\n", g15);
  unsigned n = 20U + g1;
  g1 = g10;
  g1 *= 8U;

  unsigned x = funct2();
  printf("%x\n", g1);
  unsigned d = 3U;
  (void)d;
  printf("%d\n", g15);
  unsigned f1 = 20U * 1;
  g15 = funct7();
  g4 = 5U;

  unsigned f2 = 3U;
  printf("%x\n", 10U);
  for (unsigned i = 0; i < n; i++) {
    printf("%x\n", funct2());
    unsigned y = g10;
    printf("%d\n", funct7());
    unsigned z = funct2();
    g10 = 6U;

    x = y + z;
    printf("%x\n", 0U);
    printf("%x\n", f1 * i + x * x);

    printf("%x\n", y * f2 + x);
  }
}
