#include "FenneC.h"

int j = 4;

int main() {
  if (j != 3) {
    int j = 5;
    Print(188);
    if (j == 5) {
      Print(j);
    }
    Print(23);
  }
  return 0;
}
