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
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    ll ans = 0;
    rep (i, N) {
      int t, T, x, c;
      scanf("%d%d%d%d", &t, &T, &x, &c);

      ll a = c + (t + M <= T ? 0 : M * (ll)x);
      if (t < T) {
        ll k = T - t;
        a = min(a, ll(M + k - 1) / k * c);
      }
      ans += a;
    }
    cout << ans << endl;
  }

  return 0;
}

