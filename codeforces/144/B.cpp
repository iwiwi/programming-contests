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

double sqr(double x) { return x * x; }

int main() {
  int X0, Y0, X1, Y1;
  while (4 == scanf("%d%d%d%d", &X0, &Y0, &X1, &Y1)) {
    if (X0 > X1) swap(X0, X1);
    if (Y0 > Y1) swap(Y0, Y1);
    ++X1;
    ++Y1;

    int N, X[1010], Y[1010], R[1010];
    scanf("%d", &N);
    rep (i, N) scanf("%d%d%d", &X[i], &Y[i], &R[i]);

    int ans = 0;

    for (int y = Y0; y < Y1; ++y) {
      vector<int> inc(X1 - X0);
      int c = 0;

      rep (i, N) {
        if (abs(Y[i] - y) > R[i]) continue;
        int xl = ceil (X[i] - sqrt(sqr(R[i]) - sqr(Y[i] - y)));
        int xr = floor(X[i] + sqrt(sqr(R[i]) - sqr(Y[i] - y)));
        // [xl, xr]
        ++xr;
        // [xl, xr)
        if (xl < X0) ++c;
        else if (xl < X1) ++inc[xl - X0];

        if (xr < X0) --c;
        else if (xr < X1) --inc[xr - X0];
        // printf(" %d, %d -> [%d, %d)\n", y, i, xl, xr);
      }

      for (int x = X0; x < X1; ++x) {
        c += inc[x - X0];
        if (c == 0) {
          // printf("%d %d\n", x, y);
          if (ll(X0 - x) * (X1 - x - 1) * (Y0 - y) * (Y1 - y - 1) == 0) ++ans;
        }
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}

