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

int H, W;
ll C[1010][1010];

ll sqr(ll x) { return x * x; }

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) rep (x, W) {
      int c;
      scanf("%d", &c);
      C[y][x] = c;
    }

    ll byp = -1, byt = 1LL << 60;
    ll cs[1010];
    rep (y, H) {
      cs[y] = 0;
      rep (x, W) cs[y] += C[y][x];
    }
    for (int y = 0; y <= H; ++y) {
      ll t = 0;
      rep (i, H) t += cs[i] * sqr(y * 4 - (i * 4 + 2));
      if (t < byt) {
        byp = y;
        byt = t;
      }
    }

    ll bxp = -1, bxt = 1LL << 60;
    rep (x, W) {
      cs[x] = 0;
      rep (y, H) cs[x] += C[y][x];
    }
    for (int x = 0; x <= W; ++x) {
      ll t = 0;
      rep (j, W) t += cs[j] * sqr(x * 4 - (j * 4 + 2));
      if (t < bxt) {
        bxp = x;
        bxt = t;
      }
    }

    cout << (byt + bxt) << endl;
    cout << byp << " " << bxp << endl;
  }

  return 0;
}

