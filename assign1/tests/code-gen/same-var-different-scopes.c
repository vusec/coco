#include "FenneC.h"

int i = 2;
int main() {
  {
    int i = 3;
    Print(i);
  }
  {
    int i = 4;
    Print(i);
  }
  Print(i);
  return 0;
}
