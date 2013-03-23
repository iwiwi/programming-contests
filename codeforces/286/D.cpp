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
const ll INF = 1LL << 60;

int LX[100010], RX[100010], T[100010];
int LP[100010], RP[100010];
int Q[100010];
ll ans[100010];

int main() {
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    rep (i, M) scanf("%d%d%d", &LX[i], &RX[i], &T[i]);
    rep (i, N) scanf("%d", &Q[i]);

    vector<int> X;
    rep (i, M) { X.pb(LX[i]); X.pb(RX[i]); }
    sort(all(X));
    X.erase(unique(all(X)), X.end());
    int P = X.size();

    rep (i, M) {
      LP[i] = lower_bound(all(X), LX[i]) - X.begin();
      RP[i] = lower_bound(all(X), RX[i]) - X.begin();
    }

    vector<ll> start(P, INF);
    {
      vector<vector<int> > tmp(P);
      rep (i, M) tmp[LP[i]].pb(i);

      set<pair<int, int> > se;
      rep (p, P) {
        rep (i, tmp[p].size()) {
          int k = tmp[p][i];
          se.insert(mp(T[k], RP[k]));
        }
        while (!se.empty() && se.begin()->second < p + 1) se.erase(se.begin());
        // printf("%d: %d\n", p, se.begin()->second);
        if (!se.empty()) start[p] = se.begin()->first;
      }
    }

    vector<pair<ll, ll> > change;
    rep (p, P - 1) {
      if (start[p] == INF) continue;
      ll t = start[p];
      change.pb(mp(t - X[p + 1], +1));
      change.pb(mp(t - X[p]    , -1));
      // printf("%lld : %lld -- %lld\n", t, t - X[p + 1], t - X[p]);
    }
    sort(all(change));
    size_t ci = 0;

    vector<pair<int, int> > queries(N);
    rep (i, N) queries[i] = mp(Q[i], i);
    sort(all(queries));

    ll a = 0, t0 = 0, c = 0;
    rep (iq, N) {
      ll t1 = queries[iq].first;
      // printf("t = %lld (%d, c = %lld)\n", t1, queries[iq].first, c);

      a += c * (t1 - t0);
      while (ci < change.size() && change[ci].first < t1) {
        ll dc = change[ci].second;
        a += dc * (t1 - change[ci].first);
        c += dc;
        // printf("%lld * %lld\n", dc, t1 - change[ci].first);
        ++ci;
      }

      ans[queries[iq].second] = a;
      t0 = t1;
    }
    rep (i, N) printf("%d\n", (int)ans[i]);
  }

  return 0;
}

