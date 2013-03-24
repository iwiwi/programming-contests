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

typedef long long ll;
typedef pair<int, int> pii;

vector<int> vs[50010];
vector<vector<pii> >  adj[50010];
vector<ll> dp[50010];

int main() {
  int N, T, M;
  while (3 == scanf("%d%d%d", &N, &T, &M)) {
    rep (i, N) {
      vs[i].clear();
      adj[i].clear();
      dp[i].clear();
    }

    vector<pair<pii, pii> > es;
    rep (i, M) {
      int u, v, s, e;
      scanf("%d%d%d%d", &u, &v, &s, &e);
      --u; --v;
      if (e > T) continue;  // Too late!

      es.pb(mp(mp(u, s), mp(v, e)));
      vs[u].pb(s);
      vs[v].pb(e);
    }

    vector<pair<int, pii> > ord;
    vs[0].pb(0);
    rep (v, N) {
      sort(all(vs[v]));
      vs[v].erase(unique(all(vs[v])), vs[v].end());

      int k = vs[v].size();
      adj[v].resize(k);
      dp[v].resize(k);

      rep (i, k) ord.pb(mp(vs[v][i], mp(v, i)));
    }

    rep (i, es.size()) {
      int u = es[i].F.F, v = es[i].S.F;
      int si = lower_bound(all(vs[u]), es[i].F.S) - vs[u].begin();
      int ei = lower_bound(all(vs[v]), es[i].S.S) - vs[v].begin();
      adj[u][si].pb(mp(v, ei));
    }

    sort(all(ord));
    ll lb = -1, ub = 1000000010;
    while (ub - lb > 1) {
      int x = (lb + ub) / 2;

      rep (v, N) fill(all(dp[v]), x + 10);
      dp[0][0] = 0;

      rep (i, ord.size()) {
        int v = ord[i].S.F;
        int s = ord[i].S.S;
        if (s > 0) {
          dp[v][s] = min(dp[v][s], dp[v][s - 1] + (vs[v][s] - vs[v][s - 1]));
        }
        // printf("%d %d: %d\n", v, s, (int)dp[v][s]);

        if (dp[v][s] > x) continue;  // I can't wait any more!!

        rep (i, adj[v][s].size()) {
          int tv = adj[v][s][i].F;
          int ts = adj[v][s][i].S;
          dp[tv][ts] = 0;
        }
      }

      rep (s, dp[N - 1].size()) if (dp[N - 1][s] <= x) goto ok;
      lb = x;
      continue;
   ok:
      ub = x;
    }

    if (ub <= T) printf("%d\n", (int)ub);
    else puts("-1");
    // break;
  }
}

