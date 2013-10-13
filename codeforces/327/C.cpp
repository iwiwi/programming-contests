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

ll pow_mod(ll a, ll k, ll m) {
  if (k == 0) return 1;
  ll t = pow_mod(a, k / 2, m);
  return mod(mod(t * t, m) * (k % 2 ? a : 1), m);
}

int main() {
  string A;
  ll K;
  while (cin >> A >> K) {
    int L = A.length();

    ll t = 0, p2 = 1;
    rep (i, L) {
      if (A[i] == '0' || A[i] == '5') (t += p2) %= MOD;
      (p2 *= 2) %= MOD;
    }

    ll b = p2;
    ll c = (pow_mod(b, K, MOD) - 1) * inverse(b - 1, MOD) % MOD;
    ll ans = mod(c * t, MOD);
    cout << ans << endl;
  }
}
