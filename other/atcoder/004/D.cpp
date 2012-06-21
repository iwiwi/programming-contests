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

vector<pair<int, int> > factorize(int n) {
  vector<pair<int, int> > res;
  for (int i = 2; i * i <= n; i++) {
    int c = 0;
    for (; n % i == 0; n /= i) c++;
    if (c > 0) res.push_back(make_pair(i, c));
  }
  if (n != 1) res.push_back(make_pair(n, 1));
  return res;
}

const int MAX_F = 1000010;

ll fac[MAX_F + 1];

void init_fac() {
  fac[0] = 1;
  for (int k = 1; k <= MAX_F; ++k) {
    fac[k] = fac[k - 1] * k % MOD;
  }
}

ll choose(ll n, ll k) {
  return fac[n] * inverse(fac[k], MOD) % MOD * inverse(fac[n - k], MOD) % MOD;
}

int main() {
  init_fac();

  ll N, M;
  while (cin >> N >> M) {
    ll ans = 0;
    for (int k = 0; k <= M; ++k) {
      if ((k % 2 == 0) ^ (N < 0)) (ans += choose(M, k)) %= MOD;
    }

    vector<pair<int, int> > f = factorize(abs(N));
    rep (i, f.size()) {
      ll t = f[i].second;
      (ans *= choose(M + t - 1, t)) %= MOD;
    }

    printf("%lld\n", ans);
    // break;
  }

  return 0;
}

