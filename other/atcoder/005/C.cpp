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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int H, W;
char fld[510][510];
int pot[510][510];

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) scanf("%s", fld[y]);

    deque<pair<int, int> > que;
    int gx = -1, gy = -1;
    rep (y, H) rep (x, W) {
      if (fld[y][x] == 's') {
        que.push_back(mp(x, y));
        pot[y][x] = 0;
      } else {
        pot[y][x] = 10;
        if (fld[y][x] == 'g') {
          gx = x;
          gy = y;
        }
      }
    }

    while (!que.empty()) {
      int x = que.front().first;
      int y = que.front().second;
      int p = pot[y][x];
      que.pop_front();

      rep (d, 4) {
        int tx = x + dx[d], ty = y + dy[d];
        if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
        int tp = p + (fld[ty][tx] == '#' ? 1 : 0);

        if (tp < pot[ty][tx]) {
          pot[ty][tx] = tp;
          if (p == tp) que.push_front(mp(tx, ty));
          else         que.push_back (mp(tx, ty));
        }
      }
    }

    if (pot[gy][gx] <= 2) puts("YES");
    else puts("NO");
  }

  return 0;
}

