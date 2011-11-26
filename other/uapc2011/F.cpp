#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back

typedef long long ll;

int L[30010], R[30010];
int A[30010];

int main() {
  int N, M, W, H, S;
  while (scanf("%d%d%d%d%d", &N, &M, &W, &H, &S) == 5 && (N|M|W|H|S)) {
    ll T = (W * H - S) * 2LL;

    rep (i, M) scanf("%d%d", &L[i], &R[i]);

    rep (i, M) A[i] = 0;
    rep (i, N) {
      double x, y;
      scanf("%lf%lf", &x, &y);

      int lb = -1, ub = M;
      while (ub - lb > 1) {
        int md = (lb + ub) / 2;
        double ty = L[md] + (R[md] - L[md]) * x / W;
        if (y < ty) ub = md;
        else lb = md;
      }
      ++A[ub];
    }

    int ans = 0;

    int rb = 0, a = 0;
    ll mi = 0;
    for (int lb = 0; lb < M; ++lb) {
      // [lb, rb)

      // advance rb
      rb = max(rb, lb);
      while (rb < M) {
        ll t = (L[rb] + R[rb]) * ll(W) - mi;
        if (t > T) break;
        a += A[rb];
        ++rb;
      }

      // printf("[%d, %d) : %d\n", lb, rb, a);
      ans = max(ans, a);

      // advance lb
      mi = (L[lb] + R[lb]) * ll(W);
      if (lb < rb) a -= A[lb];
    }

    printf("%d\n", N - ans);
  }
}
