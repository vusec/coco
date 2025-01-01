
#include <stdio.h>
#include <stdlib.h>

static unsigned g1 = 4U;
static unsigned g2 = 6U;
static unsigned g4 = 6U;
static int g8 = 10;
unsigned funct3() {
  unsigned result = g4;
  printf("%x\n", g4);
  result = result % 8U;
  printf("%d\n", g8);
  return result;
}

int main() {

  unsigned n = 20U + g1;

  unsigned x = g2;

  unsigned d = funct3();
  (void)d;
  g8 = -2;

  unsigned f1 = g4 * 1;
  printf("%d\n", 20);
  unsigned f2 = funct3();

  for (unsigned i = 0; i < n; i++) {
    printf("%d\n", g8);
    unsigned y = funct3();
    printf("%x\n", funct3());
    unsigned z = funct3();
    g8 = 0;
    g1 = 10U;

    x = y + z;

    printf("%x\n", f1 * i + x * x);

    printf("%x\n", y * f2 + x);
    printf("%d\n", g8);
  }
}
