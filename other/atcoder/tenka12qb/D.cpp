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


const int MAX_V = 510;

int L, R;
bool adj[MAX_V][MAX_V];

int mat[MAX_V];
bool vis[MAX_V];

int augment(int r) {
  rep (l, L) if (adj[l][r] && !vis[l]) {
    vis[l] = true;
    if (mat[l] < 0 || augment(mat[l])) {
      mat[l] = r;
      return 1;
    }
  }
  return 0;
}

int bipartite_matching() {
  int res = 0;
  memset(mat, -1, sizeof(mat));
  rep (r, R) {
    memset(vis, 0, sizeof(vis));
    res += augment(r);
  }
  return res;
}


int H, W;
char C[20][20];

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) scanf("%s", C[y]);

    bool empty = false, exist = false;
    rep (y, H) rep (x, W) empty |= C[y][x] == '.';
    rep (y, H) rep (x, W) exist |= C[y][x] == '#';
    if (!empty) { puts("-1"); continue; }
    if (!exist) { puts("0"); continue; }

    int ans = 9999;
    rep (b, 1 << H) {
      vector<int> ys, xs;
      rep (y, H) if (b & (1 << y)) ys.pb(y);

      rep (x, W) {
        rep (y, H) if ((b & (1 << y)) == 0 && C[y][x] == '#') goto aru;
        continue;
     aru:
        xs.pb(x);
      }

      L = ys.size();
      R = xs.size();
      rep (yi, ys.size()) rep (xi, xs.size()) {
        int y = ys[yi];
        int x = xs[xi];
        adj[yi][xi] = C[y][x] == '.';
      }
      int bm = bipartite_matching();
      if (bm == 0) {
        bm = -1;
        rep (yi, ys.size()) {
          int y = ys[yi];
          rep (x, W) if (C[y][x] == '.') bm = 0;
        }
        rep (xi, xs.size()) {
          int x = xs[xi];
          rep (y, H) if (C[y][x] == '.') bm = 0;
        }
      }
      ans = min(ans, L + R - bm);
    }

    printf("%d\n", ans);
  }

  return 0;
}

