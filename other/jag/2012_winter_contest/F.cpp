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

int V, E;
double P;
bool A[20][20];

double dp[1 << 14];

int main() {
  while (3 == scanf("%d%d%lf", &V, &E, &P)) {
    P /= 100.0;

    memset(A, 0, sizeof(A));
    rep (i, E) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      A[a][b] = A[b][a] = true;
    }

    rep (b, 1 << V) if (b) {
      int k = __builtin_popcount(b);
      int v = __builtin_ctz(b);

      if (k == 0) dp[b] = 1.0;  // one vertex
      else {
        double p = 0.0;

        int tb = b;
        do {
          int tk = __builtin_popcount(tb);
          if (tb & (1 << v) && 1 <= tk && 1 <= k - tk) {
            double tp = dp[tb];
            rep (v, V) rep (w, v) if (A[v][w]) {
              if (!(b & (1 << v)) || !(b & (1 << w))) continue;
              if (((tb >> v) & 1) ^ ((tb >> w) & 1)) tp *= P;
            }
            p += tp;
          }
          tb = (tb - 1) & b;
        } while (tb != b);

        dp[b] = 1.0 - p;
      }
    }

    printf("%.10f\n", dp[(1 << V) - 1]);
  }

  return 0;
}

