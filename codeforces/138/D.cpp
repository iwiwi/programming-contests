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

map<pair<pair<int, int>, pair<int, int> >, int> mem;

int H, W;
char fld[30][30];

int parity;

int grundy(int a, int b, int c, int d) {
  pair<pair<int, int>, pair<int, int> > p = mp(mp(a, b), mp(c, d));
  if (mem.count(p)) return mem[p];

  set<int> s;

  int k = 0;
  rep (y, H) rep (x, W) if ((x + y) % 2 == parity) {
    if (a < x + y && x + y < b && c < x - y && x - y < d);
    else continue;

    ++k;

    // cut here
    if (fld[y][x] == 'L') {
      s.insert(grundy(a, x + y, c, d) ^ grundy(x + y, b, c, d));
    } else if (fld[y][x] == 'R') {
      s.insert(grundy(a, b, c, x - y) ^ grundy(a, b, x - y, d));
    } else {  // 'X'
      s.insert(grundy(a, x + y, c, x - y) ^ grundy(a, x + y, x - y, d) ^
               grundy(x + y, b, c, x - y) ^ grundy(x + y, b, x - y, d));
    }
  }

  for (int k = 0; ; ++k) {
    if (s.count(k) == 0) return mem[p] = k;
  }
}

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) rep (x, W) scanf(" %c", &fld[y][x]);

    int x = 0;
    for (parity = 0; parity <= 1; ++parity) {
      mem.clear();
      x ^= grundy(-100, 100, -100, 100);
    }

    puts(x ? "WIN" : "LOSE");
  }

  return 0;
}

