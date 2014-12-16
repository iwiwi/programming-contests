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
#define eb(e) emplace_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;
const ll MOD = 1000000007;

ll fac[1010], choose[1010][1010];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll N, X, Y;

int main() {
  {
    ll x, y, z;
    cin >> N >> x >> y >> z;
    X = x + z;
    Y = y;
    if (X < Y) swap(X, Y);
  }

  // Init
  fac[0] = 1;
  for (int i = 1; i <= N; ++i) fac[i] = fac[i - 1] * i % MOD;

  choose[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    choose[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      choose[i][j] = (choose[i-1][j-1] + choose[i-1][j]) % MOD;
    }
  }

  // Special case
  if (X + Y == 0) {
    ll dp[1010];
    dp[0] = 1;
    for (ll n = 1; n <= N; ++n) {
      dp[n] = dp[n - 1];
      if (n >= 2) (dp[n] += dp[n - 2] * (n - 1)) %= MOD;
    }

    ll ans = dp[N];
    for (ll n = 1; n <= N; ++n) (ans *= N) %= MOD;

    cout << ans << endl;
    return 0;
  }

  // Grouping
  map<ll, vector<ll> > groups;
  for (ll n = 1; n <= N; ++n) {
    ll g = gcd(X - Y, n);
    ll k = n / g;
    groups[k].push_back(n);
  }

  // DP
  ll dp[1010] = {};
  dp[0] = 1;

  for (const auto &g : groups) {
    ll k = g.first;

    ll subdp1[1010] = {};
    subdp1[0] = 1;
    for (ll n : g.second) {
      // Consider using cycles with size |n|
      for (ll s = N; s >= 0; --s) {
        ll c = 1;  // Inside |t * n| elements
        for (ll t = 1; s - t * n >= 0; ++t) {
          // Update |c|
          c = c * choose[t * n - 1][n - 1] % MOD * fac[n - 1] % MOD;

          // |t| cycles
          (subdp1[s] += subdp1[s - t * n] * choose[s][t * n] % MOD * c % MOD) %= MOD;
        }
      }
    }


    ll subdp2[1010] = {};
    subdp2[0] = 1;
    for (ll c = 1; c * k <= N; ++c) {
      if (k % 2 != 0) {
        subdp2[c] = subdp2[c - 1] % MOD;
      }
      if (c >= 2) {
        (subdp2[c] += (c - 1) * subdp2[c - 2] % MOD * k) %= MOD;
      }
      (subdp1[c * k] *= subdp2[c]) %= MOD;
    }

    for (ll s = N; s >= 0; --s) {
      for (ll c = 1; s - c * k >= 0; ++c) {
        (dp[s] += choose[s][c * k] * dp[s - c * k] % MOD * subdp1[c * k]) %= MOD;
      }
    }
  }

  cout << dp[N] << endl;
  return 0;
}
