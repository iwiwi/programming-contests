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
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int N, A[110], S, sum[110];

double dp1[110][110];
double dp2[110][110][110];

int main() {
  int T;
  scanf("%d", &T);

  dp1[2][1] = 1.0;
  for (int n = 2; n < 100; ++n) {
    for (int k1 = 1; k1 < n; ++k1) {
      int k2 = n - k1;
      dp1[n + 1][k1 + 1] += dp1[n][k1] * k1 / (double)n;
      dp1[n + 1][k1 + 0] += dp1[n][k1] * k2 / (double)n;
    }
  }

  while (T--) {
    scanf("%d", &N);
    rep (i, N) scanf("%d", A + i);
    int S = accumulate(A, A + N, 0);
    rep (i, N) sum[i] = accumulate(A, A + i, 0);

    dp2[0][0][0] = 1.0;
    rep (i, N) {
      int a = A[i];

      for (int k = 0; k <= i + 1; ++k) {
        int sub = sum[i] + a;
        for (int s = 0; s <= sub; ++s) dp2[i + 1][k][s] = 0.0;
      }

      for (int k = 0; k <= i; ++k) {
        int sub = sum[i];
        for (int s = 0; s <= sub; ++s) {
          dp2[i + 1][k    ][s    ] += dp2[i][k][s];
          dp2[i + 1][k + 1][s + a] += dp2[i][k][s];
        }
      }
    }

    double res = 0.0;
    for (int k = 1; k < N; ++k) {
      double c = 0.0, t = 0.0;
      for (int s = 0; s <= S; ++s) {
        c += dp2[N][k][s];
        t += dp2[N][k][s] * abs((S - s) - s);
      }
      // printf("%f * %f\n", dp1[N][k], t / c);
      res += dp1[N][k] * (t / c);
    }
    printf("%.6f\n", res);
  }

  return 0;
}
