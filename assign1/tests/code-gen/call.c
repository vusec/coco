#include "FenneC.h"

int func1(int i) {
  return i;
}

int func2(int i, int j) {
  return j + i;
}

int func3() {
  return 3;
}

int func4() {
  return 2;
}

int main() {
  Print(func1(2));
  Print(func2(2, 3) + func3());
  Print(func2(3, 7) + func2(10, 2));
  Print(func3() + func2(4, 2));
  return 0;
}
