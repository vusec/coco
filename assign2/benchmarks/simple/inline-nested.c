#include "stdio.h"

int f19() { return 4; }
int f18() { return f19(); }
int f17() { return f18(); }
int f16() { return f17(); }
int f15() { return f16(); }
int f14() { return f15(); }
int f13() { return f14(); }
int f12() { return f13(); }
int f11() { return f12(); }
int f10() { return f11(); }
int f9() { return f10(); }
int f8() { return f9(); }
int f7() { return f8(); }
int f6() { return f7(); }
int f5() { return f6(); }
int f4() { return f5(); }
int f3() { return f4(); }
int f2() { return f3(); }
int f1() { return f2(); }

int main() {
    int i = 2;
    printf("Out: %d\n", i + 2);
    printf("Out: %d\n", f1());
}