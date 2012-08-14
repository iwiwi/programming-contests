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
  int K, B, N;
  while (3 == scanf("%d%d%d", &K, &B, &N)) {
    map<ll, int> cnt;
    cnt[0] = 1;

    ll s = 0, ans = 0;
    int z = 0;
    rep (i, N) {
      int a;
      scanf("%d", &a);

      s = (s * K + a) % (K - 1);
      if (a == 0) ++z;
      else z = 0;

      if (B == 0) {
        ans += z;
      } else {
        ll now = cnt[(s - B + (K - 1)) % (K - 1)];
        if (B == K - 1) now -= z;
        ans += now;
      }
      // printf(" %d: %lld\n", i, s);
      cnt[s] += 1;
    }

    cout << ans << endl;
  }

  return 0;
}

