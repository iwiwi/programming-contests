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

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int H, W;
char buf[510];
char fld[510][510];

int pot[510][510];

double power[1000010];


int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    memset(fld, '#', sizeof(fld));
    for (int y = 1; y <= H; ++y) {
      scanf("%s", buf);
      for (int x = 1; x <= W; ++x) fld[y][x] = buf[x - 1];
    }

    power[0] = 1.0;
    rep (i, W * H) power[i + 1] = power[i] * 0.99;

    double lb = -1.0, ub = 10;
    rep (iter, 100) {
      double md = (lb + ub) / 2.0;

      memset(pot, -1, sizeof(pot));
      queue<pair<int, int> > que;
      for (int y = 1; y <= H; ++y) {
        for (int x = 1; x <= W; ++x) {
          if (fld[y][x] == 's') {
            que.push(mp(y, x));
            pot[y][x] = 0;
          }
        }
      }

      while (!que.empty()) {
        int y = que.front().first;
        int x = que.front().second;
        que.pop();
        if (fld[y][x] == 'g') goto reach;

        int t = pot[y][x];
        double a = (fld[y][x] - '0') * power[t];
        if (a < md) continue;

        rep (d, 4) {
          int ty = y + dy[d];
          int tx = x + dx[d];
          if (fld[ty][tx] == '#') continue;
          if (pot[ty][tx] != -1) continue;
          que.push(mp(ty, tx));
          pot[ty][tx] = t + 1;
        }
      }
      ub = md;
      continue;
   reach:
      lb = md;
    }

    double ans = (lb + ub) / 2.0;
    if (ans < -0.5) puts("-1");
    else printf("%.20f\n", ans);
  }

  return 0;
}

