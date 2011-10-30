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

typedef long long ll;

const int dx[] = {1, 2,  2,  1, -1, -2, -2, -1};
const int dy[] = {2, 1, -1, -2, -2, -1,  1,  2};

vector<int> xs(4), ys(4);
vector<vector<int> > xss, yss;
vector<vector<int> > dss;

void search0(int k, int x, int y) {
  if (k == 4) {
    if (x != 0 || y != 0) return;
    xss.pb(xs);
    yss.pb(ys);
  }
  else {
    xs[k] = x;
    ys[k] = y;
    if (k >= 2 &&
        ((abs(xs[k] - xs[k - 2]) + abs(ys[k] - ys[k - 2]) == 3 && xs[k] != xs[k - 2]) ||
         (xs[k] == xs[k - 2] && ys[k] == ys[k - 2]))) {
      return;
    }

    rep (d, 8) {
      search0(k + 1, x + dx[d], y + dy[d]);
    }
  }
}

int H, W, N;
int X[100010], Y[100010];
vector<int> points[100010];
bool exists1[100010][8];
bool exists2[100010][24];

int main() {
  search0(0, 0, 0);
  // fprintf(stderr, "%d\n", (int)xss.size());

  int T;
  scanf("%d", &T);
  rep (ca, T) {
    scanf("%d%d%d", &H, &W, &N);
    rep (y, H) points[y].clear();

    rep (i, N) {
      int y, x;
      scanf("%d%d", &y, &x);
      --y; --x;
      points[y].pb(x);

      X[i] = x;
      Y[i] = y;
    }
    rep (y, H) {
      sort(all(points[y]));
    }

    ll ans = 0;

    rep (i, xss.size()) {
      int w = *max_element(all(xss[i])) - *min_element(all(xss[i])) + 1;
      int h = *max_element(all(yss[i])) - *min_element(all(yss[i])) + 1;

      if (w > W || h > H) continue;
      else ans += (W - w + 1LL) * (H - h + 1LL);
    }

    memset(exists1, 0, sizeof(exists1));
    memset(exists2, 0, sizeof(exists2));
    {
      map<pair<int, int>, int> m1;
      rep (i, 8) m1[mp(dx[i], dy[i])] = i;
      rep (i, N) {
        rep (k, 8) {
          int tx = X[i] + dx[k];
          int ty = Y[i] + dy[k];
          exists1[i][k] = (0 <= tx && tx < W && 0 <= ty && ty < H && binary_search(all(points[ty]), tx));
        }
      }

      map<pair<int, int>, int> m2;
      rep (i, xss.size()) m2[mp(xss[i][2], yss[i][2])] = 0;
      int k = 0;
      tr (m2, ite) {
        rep (i, N) {
          int tx = X[i] + ite->first.first;
          int ty = Y[i] + ite->first.second;
          exists2[i][k] = (0 <= tx && tx < W && 0 <= ty && ty < H && binary_search(all(points[ty]), tx));
        }
        ite->second = k++;
      }

      dss.resize(xss.size());
      rep (i, xss.size()) {
        dss[i].resize(4);
        dss[i][1] = m1[mp(xss[i][1], yss[i][1])];
        dss[i][2] = m2[mp(xss[i][2], yss[i][2])];
        dss[i][3] = m1[mp(xss[i][3], yss[i][3])];
      }
    }


    int cnt[16] = {0};

    rep (i, N) {  // starting point
      int x = X[i], y = Y[i];

      rep (j, xss.size()) {
        int b = 0;
        const vector<int> &dxs = xss[j];
        const vector<int> &dys = yss[j];
        const vector<int> &dds = dss[j];
        rep (k, 4) {
          int tx = x + dxs[k];
          int ty = y + dys[k];
          if (tx < 0 || W <= tx) goto dmp;
          if (ty < 0 || H <= ty) goto dmp;
          // b |= (binary_search(all(points[ty]), tx) ? 1 : 0) << k;

          if (k == 0)      b |= 1;
          else if (k == 2) b |= exists2[i][dds[k]] << k;
          else             b |= exists1[i][dds[k]] << k;
        }

        if (b == 15) {
          rep (k, 4) {
          int tx = x + dxs[k];
          int ty = y + dys[k];
          }
        }

        // ++cnt[b]; goto dmp;

        {
          int super = b, sub = super;
          do {
            // do something
            ++cnt[sub];

            sub = (sub - 1) & super;
          } while (sub != super);
        }
     dmp:;
      }
    }

    // printf("%lld\n", ans);
    // ans -= countit( 1) * 4;
    // ans += countit( 3) * 4;
    // ans += countit( 5) * 2;
    // ans -= countit( 7) * 4;
    // ans += countit(15) * 1;
    ans -= cnt[ 1] * 4;
    ans += cnt[ 3] * 4;
    ans += cnt[ 5] * 2;
    ans -= cnt[ 7] * 4;
    ans += cnt[15] * 1;

    // rep (i, 16) printf("%d: %d\n", i, cnt[i]);
    // printf("%d, %d, %d, %d\n", cnt[1], cnt[3], cnt[5], cnt[7]);

    cout << "Case " << (ca + 1) << ": " << ans << endl;
  }

  return 0;
}

