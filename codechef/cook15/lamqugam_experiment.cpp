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

const int W = 100;
const int H = 100;

bool win[H + 1][W + 1];

int main(int argc, char **argv) {
  if (argc == 0) puts("give me D");
  int d = atoi(argv[1]);

  for (int y = 1; y <= H; ++y) {
    for (int x = 1; x <= W; ++x) {
      for (int a = 1; a < x; ++a) if (!win[y][x - a]) win[y][x] = true;
      for (int a = 1; a < y; ++a) if (!win[y - a][x]) win[y][x] = true;
      for (int a = 1; a < min(x, y); ++a) if (a % d == 0 && !win[y - a][x - a]) win[y][x] = true;

      if (x == y) printf("%c", " X"[win[y][x]]);
      else printf("%c", " *"[win[y][x]]);
    }
    puts("");
  }

  return 0;
}

