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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

#define F first
#define S second

int N, R;
vector<pair<int, pair<int, int> > > fwd[50010];
vector<pair<int, pair<int, int> > > bwd[50010];

vector<int> ord;
bool vis[50010];
void toposo(int v) {
  if (vis[v]) return;
  vis[v] = true;
  rep (i, fwd[v].size()) toposo(fwd[v][i].first);
  ord.pb(v);
}

pair<int, int> fdist[50010];
pair<int, int> bdist[50010];
bool btoll[50010];
int ans[50010];

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d", &N, &R);
    if (N == 0 || R == 0) return 0;
    printf("Case %d: ", ca);

    rep (v, N) fwd[v].clear(), bwd[v].clear();
    rep (i, R) {
      int x, y, c;
      scanf("%d%d%d", &x, &y, &c);
      --x;
      --y;
      fwd[x].pb(mp(y, mp(c, i)));
      bwd[y].pb(mp(x, mp(c, i)));
    }

    ord.clear();
    memset(vis, 0, sizeof(vis));
    toposo(0);
    reverse(all(ord));

    rep (v, N) fdist[v] = bdist[v] = mp(INT_MAX, INT_MIN);
    fdist[0] = bdist[N - 1] = mp(0, 0);
    rep (k, N) {
      int v = ord[k];
      rep (i, fwd[v].size()) {
        fdist[fwd[v][i].F].F = min(fdist[fwd[v][i].F].F, fdist[v].F + fwd[v][i].S.F);
        fdist[fwd[v][i].F].S = max(fdist[fwd[v][i].F].S, fdist[v].S + fwd[v][i].S.F);
      }
    }
    int L = fdist[N - 1].S;
    // rep (v, N) printf("%d: %d %d\n", v, fdist[v].F, fdist[v].S);

    memset(btoll, 0, sizeof(btoll));
    memset(ans, -1, sizeof(ans));
    rep (k, N) {
      int v = ord[N - 1 - k];

      bool t = false;
      rep (i, fwd[v].size()) t |= btoll[fwd[v][i].F];

      if (bdist[v].F != bdist[v].S) {
        if (fdist[v].F != fdist[v].S) goto ng;
        int bd = L - fdist[v].F;
        rep (i, fwd[v].size()) {
          int w = fwd[v][i].F;
          if (btoll[w]) {
            if (bdist[w].F + fwd[v][i].S.F != bd) goto ng;
          } else {
            if (bdist[w].F + fwd[v][i].S.F > bd) goto ng;
            if (bdist[w].F + fwd[v][i].S.F < bd) ans[fwd[v][i].S.S] = bd - (bdist[w].F + fwd[v][i].S.F);
          }
        }
        t = true;
        bdist[v].F = bdist[v].S = bd;
      }

      rep (i, bwd[v].size()) {
        bdist[bwd[v][i].F].F = min(bdist[bwd[v][i].F].F, bdist[v].F + bwd[v][i].S.F);
        bdist[bwd[v][i].F].S = max(bdist[bwd[v][i].F].S, bdist[v].S + bwd[v][i].S.F);
      }

      btoll[v] = t;
      assert(bdist[v].F == bdist[v].S);
    }

    printf("%d %d\n", R - (int)count(ans, ans + R, -1), L);
    rep (i, R) if (ans[i] != -1) printf("%d %d\n", i + 1, ans[i]);
    continue;
 ng:
    puts("No solution");
  }

  return 0;
}

