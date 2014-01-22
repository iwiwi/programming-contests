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

int H, W;
char F[3010][3010];

int num[3010][3010];

void doit(int sx, int sy) {
  memset(num, 0, sizeof(num));
  num[sy][sx] = 1;

  rep (y, H) rep (x, W) {
    if (F[y][x] == '#') num[y][x] = 0;
    else {
      (num[y + 1][x] += num[y][x]) %= MOD;
      (num[y][x + 1] += num[y][x]) %= MOD;
    }
  }
}

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) scanf("%s", F[y]);

    doit(1, 0); ll a = num[H - 2][W - 1], b = num[H - 1][W - 2];
    doit(0, 1); ll c = num[H - 2][W - 1], d = num[H - 1][W - 2];
    ll ans = ((a * d - b * c) % MOD + MOD) % MOD;
    cout << ans << endl;
  }
}
