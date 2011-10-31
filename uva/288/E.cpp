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



const int MAX_K = 2500;

ll coe[MAX_K + 1][MAX_K + 1];
ll inv[MAX_K + 2];

// 1^k + 2^k + ... + n^k
ll calc(ll n, int k) {
  ll a = n, s = 0;
  rep (i, k + 1) {
    s = (s + a * coe[k][i]) % MOD;
    a = (a * n) % MOD;
  }
  return s;
}

void init(int K) {
  for (int i = 1; i <= K + 1; ++i) inv[i] = inverse(i, MOD);

  coe[1][1] = coe[1][0] = inv[2];
  for (int i = 2; i <= K; ++i) {
    for (int j = i; j > 0; --j) {
      coe[i][j] = coe[i - 1][j - 1] * inv[j + 1] % MOD;
      coe[i][j] = coe[i][j] * i % MOD;
    }
    coe[i][0] = 0;
    coe[i][0] = (1 - calc(1, i) + MOD) % MOD;
  }
}



int main() {
  int T;
  cin >> T;

  init(2500);

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
    ans = (ans - calc(N, K) + MOD) % MOD;

    printf("%lld\n", ans);
  }

  return 0;
}

