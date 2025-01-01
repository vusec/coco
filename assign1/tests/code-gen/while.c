#include "FenneC.h"

int main() {
  int i = 0;
  Print(0);
  while (i < 3) {
    i = i + 3;
    Print(i);
  }
  Print(2);
  while (i > 0) {
    i = i - 2;
    Print(i);
  }
  Print(2);
  return 0;
}
