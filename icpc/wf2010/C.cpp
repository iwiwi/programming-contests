#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define all(c) (c).begin(), (c).end()
#define mp make_pair
#define pb push_back

typedef long long ll;

const int dx[2] = {-1, 0};
const int dy[2] = {0, -1};

int realH, realW, N;
int X1[1010], Y[1010], X2[1010];
vector<int> xs, ys;

bool fld[3010][4010];

int conv_x(int realX) { return lower_bound(all(xs), realX) - xs.begin(); }
int conv_y(int realY) { return lower_bound(all(ys), realY) - ys.begin(); }

int main() {
  for (int ca = 0; ; ++ca) {
    scanf("%d%d%d", &realH, &realW, &N);
    if (realH == 0 && realW == 0) return 0;

    rep (i, N) scanf("%d%d%d%d", X1 + i, Y + i, X2 + i, Y + i);

    xs.clear(); xs.pb(0); xs.pb(realW); xs.pb(realW - 1);
    ys.clear(); ys.pb(0); ys.pb(realH); ys.pb(realH - 1);
    rep (i, N) {
      xs.pb(X1[i] - 1); xs.pb(X1[i]); xs.pb(X2[i]); xs.pb(X2[i] + 1);
      ys.pb(Y[i] - 1); ys.pb(Y[i]); ys.pb(Y[i] + 1);
    }

    sort(all(xs)); xs.erase(unique(all(xs)), xs.end()); xs.erase(remove(all(xs), -1), xs.end());
    sort(all(ys)); ys.erase(unique(all(ys)), ys.end()); ys.erase(remove(all(ys), -1), ys.end());

    int H = ys.size(), W = xs.size();
    rep (y, H) rep (x, W) fld[y][x] = false;
    rep (i, N) {
      int x1 = conv_x(X1[i]);
      int x2 = conv_x(X2[i]);
      int y = conv_y(Y[i]);
      for (int x = x1; x <= x2; ++x) fld[y][x] = true;
    }

    // for (int y = H - 1; y >= 0; --y) {
    //   rep (x, W) printf("%c", fld[y][x] ? '#' : ' ');
    //   puts("");
    // }

    queue<pair<int, int> > que;
    int x = conv_x(realW - 1);
    int y = conv_y(realH - 1);
    if (fld[y][x] == false) {
      que.push(mp(x, y));
      fld[y][x] = true;
    }

    while (!que.empty()) {
      int x = que.front().first;
      int y = que.front().second;
      que.pop();
      // ans += (xs[x + 1] - xs[x]) * ll(ys[y + 1] - ys[y]);

      rep (d, 2) {
        int tx = x + dx[d];
        int ty = y + dy[d];
        if (tx < 0 || ty < 0) continue;
        if (fld[ty][tx]) continue;

        que.push(mp(tx, ty));
        fld[ty][tx] = true;
      }
    }

    ll ans = 0;
    rep (y, H - 1) rep (x, W - 1) if (fld[y][x] == false) ans += (xs[x + 1] - xs[x]) * ll(ys[y + 1] - ys[y]);

    // for (int y = H - 1; y >= 0; --y) {
    //   rep (x, W) printf("%c", fld[y][x] ? '#' : ' ');
    //   puts("");
    // }

    cout << "Case " << ca + 1 << ": " << ans << endl;
  }
}
