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

double dst[110][110];

double V[110][110];
double A[110][110];

int main() {
  for (;;) {
    int C, R;
    scanf("%d%d", &C, &R);
    if (C == 0) return 0;

    rep (i, C) rep (j, C) {
      A[i][j] = -1.0;
      dst[i][j] = i == j ? 0.0 : 1E20;
    }

    rep (i, R) {
      int x, y;
      double v, a;
      cin >> x >> y >> v >> a;
      --x;
      --y;
      V[x][y] = V[y][x] = v;
      A[x][y] = A[y][x] = a;

      dst[x][y] = dst[y][x] = v;
    }

    rep (k, C) rep (i, C) rep (j, C) dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);

    double ans = dst[0][C - 1];
    rep (i, C) rep (j, C) {
      if (A[i][j] <= 1.0) continue;

      double t1 = dst[0][i];
      double t2 = dst[j][C - 1];

      double a = A[i][j];
      double v = V[i][j] * pow(a, -t1);

      double x = max(0.0, log(v * log(a)) / log(a));
      // printf("%d %d: %f + %f + %f + %f\n", i, j, t1, x, v * pow(a, -x), t2);
      ans = min(ans, t1 + x + v * pow(a, -x) + t2);
    }

    printf("%.3f\n", ans);
  }

  return 0;
}

