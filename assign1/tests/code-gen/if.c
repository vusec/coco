#include "FenneC.h"

int main() {
  if (1) {
    Print(1);
  }
  
  if (0) {
    Print(2);
  }

  if (1) {
    if (1) {
      Print(3);
    }
    Print(4);
  }

  if (2) {
    if (-1) {
      Print(5);
    }
    Print(6);
  }

  if (0) {
    if (-1) {
      Print(7);
    }
    Print(8);
  }
  return 0;
}
