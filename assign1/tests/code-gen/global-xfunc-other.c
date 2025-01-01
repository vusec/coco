#include "FenneC.h"

int i = 2;

void func1() {
  i = i + 2;
  i = i * 2;
}

int main() {
  func1();
  Print(i);
  return 0;
}
