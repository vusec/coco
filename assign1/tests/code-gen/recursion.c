#include "FenneC.h"

int recursing(int arg) {
  if (arg > 10)
    return arg;
  return recursing(arg + 3);
}

int main() {
  Print(recursing(4));
  Print(recursing(5));
  Print(recursing(45));
  return 0;
}
