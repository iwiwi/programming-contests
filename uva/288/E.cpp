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

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}




typedef vector<ll> poly_t;

// a(x)
ll calc(const poly_t &a, ll x) {
  ll t = 1, s = 0;
  rep (i, a.size()) {
    s = (s + t * a[i]) % MOD;
    t = (t * x) % MOD;
  }
  return (s + MOD) % MOD;
}


const int MAX_K = 2500;

poly_t sum_coef[MAX_K + 10];

void init_sum(int K) {
  static ll inv[MAX_K + 10];
  for (int i = 1; i <= K + 1; ++i) inv[i] = inverse(i, MOD);

  sum_coef[0] = poly_t(2); sum_coef[0][0] = sum_coef[0][1] = 1;
  sum_coef[1] = poly_t(3); sum_coef[1][1] = sum_coef[1][2] = inv[2];

  for (int i = 2; i <= K; ++i) {
    sum_coef[i] = poly_t(i + 2);
    for (int j = i; j > 0; --j) {
      sum_coef[i][j + 1] = sum_coef[i - 1][j] * inv[j + 1] % MOD * i % MOD;
    }
    sum_coef[i][1] = 0;
    sum_coef[i][1] = (1 - calc(sum_coef[i], 1) + MOD) % MOD;
  }
}




int main() {
  int T;
  cin >> T;

  init_sum(2500);

  while (T--) {
    ll N;
    int K;
    cin >> N >> K;

    ll t = (N * (1 + N) / 2) % MOD;;
    ll ans = 1;
    rep (i, K) {
      ans *= t;
      ans %= MOD;
    }

    // printf("%lld\n", calc(N, K));
    ans = (ans - calc(sum_coef[K], N) + MOD) % MOD;

    printf("%lld\n", ans);
  }

  return 0;
}

