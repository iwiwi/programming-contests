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
const ll MOD = 10007;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}

ll fac[MOD], inv[MOD];

void init() {
  fac[0] = 1;
  for (int i = 1; i < MOD; i++) {
    fac[i] = (fac[i - 1] * i) % MOD;
    inv[i] = inverse(i, MOD);
  }
}

ll choose_mod(ll n, ll m) {
  if (n == 0 && m == 0) return 1;
  int a = n % MOD, b = m % MOD;
  if (b > a) return 0;
  return (((((choose_mod(n / MOD, m / MOD) * fac[a]) % MOD)
            * inv[fac[b]]) % MOD) * inv[fac[a - b]]) % MOD;
}

ll count_ok(ll N, ll R) {
  if (R < N) return 0;
  ll p = N;
  ll n = R - N;

  return choose_mod(n + 2 * p, p)
      * (n + 1) % MOD
      * inverse(n + p + 1, MOD) % MOD;
}

ll count_all(ll N, ll R) {
  return choose_mod(N + R - 1, N);
}

int main() {
  init();

  int T;
  cin >> T;
  rep (t, T) {
    ll R, C, N;
    cin >> R >> C >> N;

    ll ok1 = count_ok(N, R), all1 = count_all(N, R);
    ll ok2 = count_ok(N, C), all2 = count_all(N, C);
    cout << mod(all1 * all2 - ok1 * ok2, MOD) << endl;
  }

  return 0;
}

