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

typedef long long ll;

vector<pair<int, pair<int, int> > > adj[110][3300];
vector<int> P[110];
int K[110];

int pot[110][3300];

int main() {
  int N, F, M;
  scanf("%d%d%d", &N, &F, &M);

  int bi[110], fi[110], T[110], bj[110], fj[110];
  rep (i, M) {
    scanf("%d%d%d%d%d", &bi[i], &fi[i], &T[i], &bj[i], &fj[i]);
    --bi[i];
    --fi[i];
    --bj[i];
    --fj[i];
    P[bi[i]].pb(fi[i]);
    P[bj[i]].pb(fj[i]);
  }

  int Q;
  scanf("%d", &Q);
  int bq[2100], fq[2010];
  rep (i, Q) {
    scanf("%d%d", &bq[i], &fq[i]);
    --bq[i];
    --fq[i];
    P[bq[i]].pb(fq[i]);
  }

  rep (i, N) {
    P[i].pb(0);
    P[i].pb(F);
    sort(all(P[i]));
    P[i].erase(unique(all(P[i])), P[i].end());
    K[i] = P[i].size();

    rep (k, K[i]) {
      adj[i][k].clear();
      if (k - 1 >= 0)   adj[i][k].pb(mp(P[i][k] - P[i][k - 1], mp(i, k - 1)));
      if (k + 1 < K[i]) adj[i][k].pb(mp(P[i][k + 1] - P[i][k], mp(i, k + 1)));
    }
    if (i - 1 >= 0) adj[i][0].pb(mp(1, mp(i - 1, 0)));
    if (i + 1 < N)  adj[i][0].pb(mp(1, mp(i + 1, 0)));
  }

  rep (i, M) {
    int ki = lower_bound(all(P[bi[i]]), fi[i]) - P[bi[i]].begin();
    int kj = lower_bound(all(P[bj[i]]), fj[i]) - P[bj[i]].begin();
    adj[bi[i]][ki].pb(mp(T[i], mp(bj[i], kj)));
    adj[bj[i]][kj].pb(mp(T[i], mp(bi[i], ki)));
  }

  rep (i, Q) {
    int bs = bq[i];
    int ks = lower_bound(all(P[bs]), fq[i]) - P[bs].begin();

    rep (i, N) rep (k, K[i]) pot[i][k] = INT_MAX;
    typedef pair<int, pair<int, int> > piii;
    priority_queue<piii, vector<piii>, greater<piii> > que;

    pot[bs][ks] = 0;
    que.push(mp(0, mp(bs, ks)));
    while (!que.empty()) {
      int t = que.top().first;
      int b = que.top().second.first;
      int k = que.top().second.second;
      que.pop();
      if (t > pot[b][k]) continue;

      rep (i, adj[b][k].size()) {
        int tt = t + adj[b][k][i].first;
        int tb = adj[b][k][i].second.first;
        int tk = adj[b][k][i].second.second;
        if (tt < pot[tb][tk]) {
          pot[tb][tk] = tt;
          que.push(mp(tt, mp(tb, tk)));
        }
      }
    }

    ll ans = 0;
    rep (i, N) if (i != bs) {
      rep (k, K[i] - 1) {
        int t0 = pot[i][k];
        int t1 = pot[i][k + 1];
        int c = P[i][k + 1] - P[i][k];

        int x = min(max((t1 - t0 + c) / 2 + 1, 0), c);
        // [0, x), [x, c)
        if (x > 0) {
          int n = x;
          ans += t0 * ll(n) + n * ll(n - 1) / 2;
        }
        if (x < c) {
          int n = c - x;
          ans += t1 * ll(n) + n * ll(n + 1) / 2;
        }

        /*
        rep (f, c) {
          if (f < x) ans += t0 + f;
          else ans += t1 + c - f;
        }
        */

        /*
        for (int f = P[i][k]; f < P[i][k + 1]; ++f) {
          ans += min(t0 + (f - P[i][k]), t1 + (P[i][k + 1] - f));
        }
        */
      }
    }
    cout << ans << endl;
  }

  return 0;
}

