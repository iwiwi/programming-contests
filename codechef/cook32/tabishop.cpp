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
typedef pair<ll, ll> pll;

int N, K, M;
ll ans;

vector<pair<ll, pll> > enumerate_lines(map<ll, vector<pair<ll, bool> > > &P) {
  vector<pair<ll, pll> > lines;

  tr (P, ite) {
    ll p = ite->first;
    vector<pair<ll, bool> > &v = ite->second;
    sort(all(v));

    ll prv_q = INT_MIN;
    bool mid_b = false;

    // printf("p=%lld\n", p);
    rep (i, v.size()) {
      // printf(" %lld(%d)\n", v[i].first, v[i].second);
      if (v[i].second) {  // Bishop!
        mid_b = true;
      } else {
        ll q = v[i].first;
        if (prv_q != INT_MIN && mid_b) {
          lines.pb(mp(p, mp(prv_q, q)));
          // printf("[%lld, %lld)\n", prv_q, q);
          assert((q - prv_q) % 2 == 0);
          ans += (q - prv_q) / 2;
        }

        mid_b = false;
        prv_q = v[i].first + 2;
      }
    }
  }

  // puts("--"); rep (i, lines.size()) printf("%lld, [%lld, %lld)\n", lines[i].first, lines[i].second.first, lines[i].second.second);
  return lines;
}

typedef long long val_t;

val_t sum(int i, val_t *bit) {
  val_t s = 0;
  for (; i > 0; i -= i & -i) s += bit[i];
  return s;
}

void add(int i, val_t v, val_t *bit, int n) {
  for (; i <= n; i += i & -i) bit[i] += v;
}

ll bit[1000010];

ll count_cross(const vector<pair<ll, pll> > &yoko, const vector<pair<ll, pll> > &tate) {
  map<ll, int> ys;
  rep (i, yoko.size()) ys[yoko[i].F] = 0;
  rep (i, tate.size()) ys[tate[i].S.F] = ys[tate[i].S.S] = 0;
  int Y = 1;
  tr (ys, ite) ite->second = Y++;
  memset(bit, 0, sizeof(bit));

  vector<pair<ll, int> > evt;
  rep (i, yoko.size()) evt.pb(mp(yoko[i].S.F, ~i));
  rep (i, yoko.size()) evt.pb(mp(yoko[i].S.S, ~i));
  rep (i, tate.size()) evt.pb(mp(tate[i].F, i));
  sort(all(evt));

  ll ans = 0;
  rep (i, evt.size()) {
    ll x = evt[i].first;

    int k = evt[i].second;
    if (k < 0) {  // yoko
      k = ~k;
      int yi = ys[yoko[k].F], d;
      if (x == yoko[k].S.F) d = +1;
      else                  d = -1;
      add(yi, d, bit, Y);
      // printf(" %d, %d\n", yi, d);
    } else {
      int yi0 = ys[tate[k].S.F];
      int yi1 = ys[tate[k].S.S];
      ans += sum(yi1 - 1, bit) - sum(yi0 - 1, bit);
      // printf(" [%d, %d)\n", yi0, yi1);
      // printf("%lld: %lld\n", x, ans);
    }
  }
  return ans;
}

vector<vector<pair<ll, pll> > > divide_parity(const vector<pair<ll, pll> > &pls) {
  vector<vector<pair<ll, pll> > > res(2);
  rep (i, pls.size()) res[abs(pls[i].F % 2)].pb(pls[i]);
  return res;
}

int main() {
  while (3 == scanf("%d%d%d", &N, &K, &M)) {
    --N;  // -> [0, N] !!

    map<ll, vector<pair<ll, bool> > > P, Q;

    rep (i, K + M) {
      int x, y;
      scanf("%d%d", &x, &y);
      --x; --y;
      P[x + y].pb(mp(x - y, i < K));
      Q[x - y].pb(mp(x + y, i < K));
    }

    tr (P, ite) {
      ll p = ite->first;
      if (p <= N) { ite->second.pb(mp(-p   -2, 0)); ite->second.pb(mp(p    +2, 0)); }
      else        { ite->second.pb(mp(p-N-N-2, 0)); ite->second.pb(mp(N+N-p+2, 0)); }
    }
    tr (Q, ite) {
      ll q = ite->first;
      if (q >= 0) { ite->second.pb(mp( q-2, 0)); ite->second.pb(mp(N+N-q+2, 0)); }
      else        { ite->second.pb(mp(-q-2, 0)); ite->second.pb(mp(N+N+q+2, 0)); }

    }

    ans = 0;
    vector<vector<pair<ll, pll> > >
        pls = divide_parity(enumerate_lines(P)),
        qls = divide_parity(enumerate_lines(Q));

    // printf("lines -> %lld\n", ans);

    rep (i, 2) ans -= count_cross(pls[i], qls[i]);

    // printf("cross -> %lld\n", ans);
    cout << ans << endl;
  }

  return 0;
}

