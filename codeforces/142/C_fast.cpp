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

int W, H;
char fld[10][10];

int best;
char best_fld[10][10];

const char *P[][3] =
  {
    {"###", ".#.", ".#."},
    {"..#", "###", "..#"},
    {".#.", ".#.", "###"},
    {"#..", "###", "#.."},
  };

void search(int x, int y, int c) {
  if (x == W) search(0, y + 1, c);
  else if (y == H) {
    if (c <= best) return;
    best = c;
    rep (ty, H) rep (tx, W) best_fld[ty][tx] = fld[ty][tx];
  }
  else {
    int r = 0;
    for (int ty = y; ty < H; ++ty) {
      for (int tx = ty == y ? x : 0; tx < W; ++tx) {
        if (fld[ty][tx] == '.') ++r;
      }
    }
    if (c + r / 5 <= best) return;  // no chance

    if (x + 3 <= W && y + 3 <= H) {
      rep (d, 4) {
        rep (dx, 3) rep (dy, 3) {
           if (P[d][dy][dx] == '.') continue;
          if (fld[y + dy][x + dx] != '.') goto ng;
        }

        rep (dx, 3) rep (dy, 3) if (P[d][dy][dx] == '#') fld[y + dy][x + dx] = 'A' + c;
        search(x + 1, y, c + 1);
        rep (dx, 3) rep (dy, 3) if (P[d][dy][dx] == '#') fld[y + dy][x + dx] = '.';
      ng:;
      }
    }

    search(x + 1, y, c);
  }
}

void show(const char **t, int n) {
  rep (i, n) puts(t[i]);
}

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    best = -1;
    memset(fld, '.', sizeof(fld));
    search(0, 0, 0);

    printf("%d\n", best);
    rep (y, H) {
      rep (x, W) printf("%c", best_fld[y][x]);
      puts("");
    }
  }

  return 0;
}

