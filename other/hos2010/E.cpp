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

const int D = 10000;

inline double sqr(double x) {
  return x * x;
}

/*
inline double calc_r2(double a, double b, double th) {
  return 1.0 / (sqr(cos(th) / a) + sqr(sin(th) / b));
}
*/

inline double calc_r2(double a, double b, double th) {
  return 1.0 / (1.0 / sqr(a) + (1.0 / sqr(b) - 1.0 / sqr(a)) * sqr(sin(th)));
}

int N;
double A[20], B[20], T[20], K[20];
double a[20], b[20];

int main() {
  for (;;) {
    scanf("%d", &N);
    if (N == 0) return 0;

    rep (i, N) {
      scanf("%lf%lf%lf%lf", A + i, B + i, T + i, K + i);
      T[i] = T[i] / 180 * M_PI;
      a[i] = A[i] * K[i] / 100.0;
      b[i] = B[i] * K[i] / 100.0;
    }

    double ans = 0.0;
    rep (i, D) {
      double th = 2 * M_PI * i / D;
      double R2 = 1E10, r2 = -1E10;
      rep (i, N) R2 = min(R2, calc_r2(A[i], B[i], th - T[i]));
      rep (i, N) r2 = max(r2, calc_r2(a[i], b[i], th - T[i]));
      if (r2 < R2) ans += R2 - r2;
    }

    ans *= (2 * M_PI / D) / 2.0;
    printf("%.10f\n", ans);
  }
}

