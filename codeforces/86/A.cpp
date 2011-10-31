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

int len(ll x) {
  int l = 1;
  for (x /= 10; x > 0; x /= 10) l++;
  return l;
}

ll pow10(int p) {
  ll r = 1;
  for (; p > 0; p--) r *= 10;
  return r;
}




int main() {
  ll L, R;
  while (cin >> L >> R) {
    ll ans = 0;

    int k = len(R);
    ll S = pow10(k) - 1;
    if (len(L) == len(S)) ans = max(ans, L * (S - L));
    if (len(R) == len(S)) ans = max(ans, R * (S - R));

    for (int i = 1; i <= k; ++i) {
      ll s = pow10(i) - 1;
      {
        ll t = s / 2;
        if (L <= t && t <= R) ans = max(ans, t * (s - t));
        // cout << s << " " << t << endl;
      }
      {
        ll t = (s + 1) / 2;
        if (L <= t && t <= R) ans = max(ans, t * (s - t));
      }
    }

    cout << ans << endl;
  }

  return 0;
}

