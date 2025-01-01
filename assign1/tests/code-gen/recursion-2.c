#include "FenneC.h"

int other(int arg) {
  return arg;
}

int recursing2(int arg) {
  if (arg < other(10))
    return recursing2(arg + 3);
  return arg;
}

int main() {
  Print(recursing2(8));
  Print(recursing2(3));
  Print(recursing2(22));
  return 0;
}
