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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef bitset<3000010> bs_t;
const int MOD = 100000;

int main() {
  int K, R;
  while (2 == scanf("%d%d", &K, &R)) {
    bs_t mz[2];

    rep (i, R) {
      int t, a;
      scanf("%d%d", &t, &a);
      mz[t - 1][a] = true;
    }

    int dp[3][3] = {};
    dp[1][1] = 1;
    for (int i = 1; i <= K; ++i) {
      bool ax = mz[0][i];
      bool bx = mz[1][i];

      rep (j, 3) dp[j][2] = dp[2][j] = 0;
      rep (a, 2) rep (b, 2) {
        if (a == 0 && b == 0) continue;
        if (!ax) dp[2][b] += dp[a][b];
        if (!bx) dp[a][2] += dp[a][b];
        if (!ax && !bx) dp[2][2] += dp[a][b];
      }

      rep (a, 2) rep (b, 2) dp[a][b] = dp[a + 1][b + 1] % MOD;
    }

    printf("%d\n", dp[1][1]);
  }

  return 0;
}

