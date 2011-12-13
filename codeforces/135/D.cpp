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
const int dy[4] = {0, -1, 0, 1};

int H, W;
char fld[1010][1010];
bool vis[1010][1010][4];
bool now[1010][1010];
int ans = 0;

void doit(int x0, int y0) {
  int d = 0, sd = 0;
  vector<int> xs, ys;

  vector<int> xt, yt;

  for (int x = x0, y = y0;;) {
    int td, dd;
    for (dd = 1; dd >= -1; --dd) {
      td = (d + dd + 4) % 4;
      int tx = x + dx[td];
      int ty = y + dy[td];
      if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
      if (fld[ty][tx] == '1') goto ok;
    }
    break;


 ok:;
    // printf("%d, %d: %d\n", x, y, d);

    sd += dd;
    d = td;
    if (x == x0 && y == y0 && d != 0) return;  // bad start...

    if (d == 0 && y > 0 && fld[y - 1][x] == '0') {
      xt.pb(x);
      yt.pb(y - 1);
    }

    if (vis[y][x][d]) break;
    vis[y][x][d] = true;
    xs.pb(x);
    ys.pb(y);

    x += dx[d];
    y += dy[d];
  }

  // printf("sd = %d\n" , sd);

  // rep (i, xs.size()) printf("%d %d, ", xs[i], ys[i]); puts("");
  int len = xs.size();
  if (sd != 4 || len < 4 || abs(xs.front() - xs.back()) + abs(ys.front() - ys.back()) != 1) return;
  // puts("OK1");

  bool ok = true;
  rep (i, xs.size()) {
    if (now[ys[i]][xs[i]]) ok = false;
    now[ys[i]][xs[i]] = true;
  }
  rep (i, xs.size()) {
    int c = 0;
    rep (d, 4) {
      int tx = xs[i] + dx[d];
      int ty = ys[i] + dy[d];
      if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
      if (now[ty][tx]) ++c;
    }
    if (c != 2) ok = false;
    // printf(" %d %d: %d\n", xs[i], ys[i], c);
  }
  // if (ok) puts("OK2");

  {
    queue<pair<int, int> > que;
    rep (i, xt.size()) {
      que.push(mp(xt[i], yt[i]));
      now[yt[i]][xt[i]] = true;
      xs.pb(xt[i]);
      ys.pb(yt[i]);
      //   printf(" %d %d\n", xt[i], yt[i]);
    }
    while (!que.empty()) {
      int x = que.front().first;
      int y = que.front().second;
      que.pop();
      if (fld[y][x] == '1') {
        ok = false;
        break;
      }


      rep (d, 4) {
        int tx = x + dx[d];
        int ty = y + dy[d];
        if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
        if (!now[ty][tx]) {
          now[ty][tx] = true;
          xs.pb(tx);
          ys.pb(ty);
          que.push(mp(tx, ty));
        }
      }
    }
  }

  rep (i, xs.size()) now[ys[i]][xs[i]] = false;
  if (!ok) return;
  //  puts("OK3");

  ans = max(ans, len);
}

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) scanf("%s", fld[y]);

    ans = 0;

    rep (y, H - 1) rep (x, W - 1) {
      int c = 0;
      rep (dx, 2) rep (dy, 2) c += fld[y + dy][x + dx] - '0';
      if (c == 4) ans = 4;
    }

    memset(vis, 0, sizeof(vis));
    rep (y, H) rep (x, W) {
      if (!vis[y][x][0] && fld[y][x] == '1' && y > 0 && fld[y - 1][x] == '0') {
        doit(x, y);
      }
    }
    printf("%d\n", ans);
    fprintf(stderr, "--\n");
  }

  return 0;
}

