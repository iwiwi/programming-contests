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

ll rev(ll x) {
  ll r = 0;
  for (; x > 0; x /= 10) r = r * 10 + x % 10;
  return r;
}

int cnt[100010];

pair<int, int> getit(int x) {
  int r = rev(x);
  int g = __gcd(x, r);
  return mp(x / g, r / g);
}

int main() {
  int X, Y, W;
  while (3 == scanf("%d%d%d", &X, &Y, &W)) {
    map<pair<int, int>, vector<int> > yma;
    for (int y = 1; y <= Y; ++y) {
      yma[getit(y)].pb(y);
    }


    memset(cnt, 0, sizeof(cnt));
    ll ans = -1;
    pair<int, int> ansxy;

    ll crr = 0;
    int y = Y;
    for (int x = 1; x <= X; ++x) {
      pair<int, int> xp = getit(x);
      pair<int, int> yp = mp(xp.second, xp.first);

      const vector<int> &ys = yma[yp];
      rep (i, ys.size()) {
        ++cnt[ys[i]];
        if (ys[i] <= y) ++crr;
        // printf(" %d", ys[i]);
      }
      // puts("");

      while (y > 1 && crr - cnt[y] >= W) {
        crr -= cnt[y];
        --y;
      }
      // printf("%d: %d, %lld\n", x, y, crr);
      if (crr >= W) {
        ll tmp = x * ll(y);
        if (ans == -1 || tmp < ans) {
          ans = tmp;
          ansxy = mp(x, y);
        }
      }
    }

    if (ans == -1) puts("-1");
    else printf("%d %d\n", ansxy.first, ansxy.second);
  }

  return 0;
}

