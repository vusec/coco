
#include <stdio.h>
#include <stdlib.h>

static int g4 = -8;
static int g8 = 20;
static int g10 = 6;
static unsigned g15 = 1U;
int funct3() {
  int result = g4;
  result = result - 1;
  return result;
}
int funct9() {
  int result = g10;
  printf("%d\n", g10);
  result = result % g8;
  printf("%d\n", 4);
  return result;
}
unsigned funct1() {
  unsigned result = 8U;
  printf("%d\n", funct3());
  result = result + 5U;
  g8 = funct9();
  return result;
}

int main() {
  printf("%x\n", g15);
  unsigned n = 20U + 4U;
  printf("%x\n", 10U);
  unsigned x = funct1();

  unsigned d = g15;
  (void)d;

  unsigned f1 = 3U * 1;
  printf("%d\n", g10);
  unsigned f2 = 8U;

  for (unsigned i = 0; i < n; i++) {

    unsigned y = 1U;
    g15 *= g15;

    unsigned z = 5U;
    printf("%d\n", 0);
    x = y + z;
    g4 = -2;

    printf("%x\n", f1 * i + x * x);

    printf("%x\n", y * f2 + x);
    printf("%x\n", 8U);
  }
}
