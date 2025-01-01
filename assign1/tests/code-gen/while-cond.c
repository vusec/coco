#include "FenneC.h"

int global = 0;

int getCond() {
  Print(global);
  global = global + 1;
  return global < 3;
}

int main() {
  Print(0);
  while (getCond()) {
    Print(1);
  }
  Print(2);
  return 0;
}
