
#include <stdio.h>

namespace XYZ {

static int x = 1;

struct A {
  int x;
  int y;
  void a() const { return x + y; }
};

int main() {
  A var;
  printf("Hello world!\n");
  return 0;
}

}  // XYZ
