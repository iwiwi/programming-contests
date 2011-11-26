#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  int R, C;
  while (cin >> R >> C && (R | C)) {
    if (R % 2 && C % 2) puts("no");
    else puts("yes");
  }
}
