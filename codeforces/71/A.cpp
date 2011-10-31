#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)



int main() {
  int X, Y;
  while (2 == scanf("%d%d", &X, &Y)) {
    for (;;) {
      // Ciel
      for (int x = 2; x >= 0; --x) {
        int y = (220 - x * 100) / 10;
        if (x <= X && y <= Y) {
          X -= x;
          Y -= y;
          goto ok1;
        }
      }
      puts("Hanako");
      break;
   ok1:;
      // Hanako
      for (int x = 0; x <= 2; ++x) {
        int y = (220 - x * 100) / 10;
        if (x <= X && y <= Y) {
          X -= x;
          Y -= y;
          goto ok2;
        }
      }
      puts("Ciel");
      break;
   ok2:;
    }
  }

  return 0;
}

