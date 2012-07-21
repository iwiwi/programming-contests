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

const int dy[4] = {1, 0, -1, 0};
const int dx[4] = {0, 1, 0, -1};

int H, W;
bool fld[2010][2010];

char buf[2010];
bool vis[2010][2010];

int zid[2010][2010];

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) {
      scanf("%s", buf);
      rep (x, W) fld[y][x] = buf[x] == 'o';
    }

    int cnt[10] = {};

    memset(vis, 0, sizeof(vis));
    int Z = 0;
    rep (sy, H) rep (sx, W) if (!fld[sy][sx] && !vis[sy][sx]) {
      queue<pair<int, int> > que;
      que.push(mp(sx, sy));

      while (!que.empty()) {
        int x = que.front().first;
        int y = que.front().second;
        que.pop();

        zid[y][x] = Z;

        rep (d, 4) {
          int tx = x + dx[d];
          int ty = y + dy[d];
          if (tx < 0 || ty < 0 || W <= tx || H <= ty) continue;
          if (fld[ty][tx] || vis[ty][tx]) continue;
          que.push(mp(tx, ty));
          vis[ty][tx] = true;
        }
      }

      ++Z;
    }

    rep (sy, H) rep (sx, W) if (fld[sy][sx] && !vis[sy][sx]) {
      queue<pair<int, int> > que;
      que.push(mp(sx, sy));
      vis[sy][sx] = true;
      vector<int> zs;

      while (!que.empty()) {
        int x = que.front().first;
        int y = que.front().second;
        que.pop();

        for (int dx = -1; dx <= 1; ++dx) {
          for (int dy = -1; dy <= 1; ++dy) {
            int tx = x + dx;
            int ty = y + dy;
            if (!fld[ty][tx]) {
              zs.pb(zid[ty][tx]);
            } else {
              if (vis[ty][tx]) continue;
              que.push(mp(tx, ty));
              vis[ty][tx] = true;
            }
          }
        }
      }

      sort(all(zs));
      int c = unique(all(zs)) - zs.begin();
      ++cnt[c - 1];
    }

    printf("%d %d %d\n", cnt[1], cnt[2], cnt[0]);
  }

  return 0;
}

