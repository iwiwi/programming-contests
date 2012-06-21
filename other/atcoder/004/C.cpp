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

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
  ll X, Y;
  char dummy;
  while (cin >> X >> dummy >> Y) {
    // cout << X << " " << Y << endl;

    double a = X / (double)Y * 2.0;

    bool out = false;
    for (ll n = max(1, (int)floor(a) - 10); n <= (int)ceil(a) + 10; ++n) {
      ll g1 = gcd(X, Y);
      ll g2 = gcd(2 * n, Y / g1);
      // printf("%lld %lld %lld\n", n, g1, g2);
      if (g1 * g2 != Y) continue;

      ll m = n * (n + 1) - (X / g1) * (2 * n / g2);
      if (m % 2 != 0) continue;
      m /= 2;
      if (1 <= m && m <= n) {
        printf("%lld %lld\n", n, m);
        out = true;
      }
    }

    if (!out) puts("Impossible");

    break;
  }

  return 0;
}

