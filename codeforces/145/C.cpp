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

const ll MOD = 1000000007;

typedef long long ll;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}



bool is_lucky(int a) {
  while (a > 0) {
    int d = a % 10;
    if (d != 4 && d != 7) return false;
    a /= 10;
  }
  return true;
}

ll choose[1000010];

int main() {
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    ll R = 0;
    map<int, int> ma;

    rep (i, N) {
      int a;
      scanf("%d", &a);
      if (is_lucky(a)) ++ma[a];
      else ++R;
    }

    int K = 0;
    vector<ll> C(ma.size());
    tr (ma, ite) C[K++] = ite->second;

    vector<ll> dp(K + 1, 0);
    dp[0] = 1;
    rep (i, K) {
      vector<ll> nxt(K + 1, 0);
      for (int k = 0; k <= K; ++k) {
        // not-select
        nxt[k] = (nxt[k] + dp[k]) % MOD;
        // select
        if (k + 1 <= K) nxt[k + 1] = (nxt[k + 1] + dp[k] * C[i]) % MOD;
      }
      dp.swap(nxt);
    }

    choose[0] = 1;
    for (int i = 1; i <= R; ++i) {
      choose[i] =
          choose[i - 1]
          * (R - i + 1) % MOD
          * inverse(i, MOD) % MOD;
    }

    ll ans = 0;
    for (int k = 0; k <= K; ++k) {
      ll r = M - k;
      if (r < 0 || R < r) continue;
      ans += dp[k] * choose[r];
      ans %= MOD;
    }

    cout << ans << endl;
  }

  return 0;
}

