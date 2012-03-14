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

ll L, R;  // [L, R)
vector<pair<ll, ll> > itvs[40];

ll len(int s) {
  return (1LL << s) - 1;
}

void search(ll l, ll r, int s) {  // [l, r)
  if (R <= l || r <= L) return;
  if (L <= l && r <= R) {
    for (int i = 1; i <= s; ++i) itvs[i].pb(mp(0, len(i)));
    return;
  }

  // printf("%d (%lld): [%lld, %lld)\n", s, len(s), l, r);

  int c = (l + r) / 2;
  if (L <= c && c <= R) {
    ll tl = max(l, L) % (1LL << s);
    ll tr = min(r, R) % (1LL << s);
    // printf(" [%lld, %lld)\n", tl, tr);
    // assert(tl <= tr);
    itvs[s].pb(mp(tl, tr));
  }

  search(l    , c, s - 1);
  search(c + 1, r, s - 1);
}

ll L1, R1, L2, R2;
vector<pair<ll, ll> > itvs1[40], itvs2[40];

int main() {
  while (cin >> L1 >> R1 >> L2 >> R2) {
    --L1;
    --L2;

    {
      L = L1; R = R1;
      for (int i = 1; i <= 30; ++i) itvs[i].clear();
      search(0, len(30), 30);
      for (int i = 1; i <= 30; ++i) itvs1[i] = itvs[i];
    }
    {
      L = L2; R = R2;
      for (int i = 1; i <= 30; ++i) itvs[i].clear();
      search(0, len(30), 30);
      for (int i = 1; i <= 30; ++i) itvs2[i] = itvs[i];
    }

    ll ans = 0;
    for (int i = 1; i <= 30; ++i) {
      rep (j1, itvs1[i].size()) {
        rep (j2, itvs2[i].size()) {
          pair<ll, ll> t1 = itvs1[i][j1];
          pair<ll, ll> t2 = itvs2[i][j2];
          ll x = min(t1.second, t2.second) - max(t1.first, t2.first);
          ans = max(ans, x);
        }
      }
    }
    cout << ans << endl;

    // for (int i = 1; i <= 30; ++i) {
    //   printf("%d: ", i);
    //   rep (j, itvs[i].size()) printf("[%lld, %lld) ", itvs[i][j].first, itvs[i][j].second);
    //   puts("");
    // }
    // break;
  }
  return 0;
}

