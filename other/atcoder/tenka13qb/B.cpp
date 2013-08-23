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

int main() {
  ll Q, L;
  while (2 == scanf("%lld%lld", &Q, &L)) {
    vector<pair<ll, ll> > stk;  // (value, length)
    ll sz = 0;

    rep (q, Q) {
      char s[256];
      ll n, v;
      scanf("%s", s);
      if (s[1] == 'u') {  // Push
        scanf("%lld%lld", &n, &v);
        if (sz + n > L) {
          puts("FULL");
          goto err;
        } else {
          stk.pb(mp(v, n));
          sz += n;
        }
      } else if (s[0] == 'P') {  // Pop
        scanf("%lld", &n);
        while (n > 0) {
          if (sz == 0) {
            puts("EMPTY");
            goto err;
          } else {
            ll k = min(n, stk.back().second);
            n -= k;
            stk.back().second -= k;
            sz -= k;
            if (stk.back().second == 0) stk.pop_back();
          }
        }
      } else if (s[0] == 'T') {  // Top
        if (sz == 0) {
          puts("EMPTY");
          goto err;
        } else {
          printf("%lld\n", stk.back().first);
        }
      } else if (s[0] == 'S') {  // Size
        printf("%lld\n", sz);
      }
    }

    puts("SAFE");
 err:;
  }

  return 0;
}

