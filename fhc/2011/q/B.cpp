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



int main() {
  int N;
  scanf("%d", &N);
  rep (ca, N) {
    bool fld[110][210];
    memset(fld, 0, sizeof(fld));
    int R, C, K, M;
    scanf("%d%d%d%d", &R, &C, &K, &M);
    int W = C * 2 - 1;

    for (int y = 0; y < R; ++y) {
      for (int x = y % 2; x < W; x += 2) fld[y][x] = true;
    }

    rep (i, M) {
      int r, c;
      scanf("%d%d", &r, &c);
      int x = r % 2 + c * 2;
      fld[r][x] = false;
    }

    /*
    rep (y, R) {
      rep (x, W) printf("%c", fld[y][x] ? '#' : ' ');
      puts("");
    }
    puts("");
    */

    vector<double> dp(W);
    dp[1 + K * 2] = 1.0;
    for (int y = R - 1; y >= 0; --y) {
      vector<double> nxt(W, 0.0);

      int xlb = 0, xub = W;
      if (y % 2 == 1) xlb = 1, xub = W - 1;

      for (int x = xlb; x < xub; ++x) {
        if (fld[y][x]) {
          if (x == xlb) nxt[x] = dp[x + 1];
          else if (x == xub - 1) nxt[x] = dp[x - 1];
          else nxt[x] = 0.5 * (dp[x - 1] + dp[x + 1]);
        }
        else nxt[x] = dp[x];

        // printf("%f ", nxt[x]);
      }
      // puts("");
      dp = nxt;
    }

    double bestp = 0.0;
    int bestx = -1;
    for (int x = 1; x < W; x += 2) {
      if (dp[x] > bestp) {
        bestp = dp[x];
        bestx = x;
      }
    }
    printf("%d %.6f\n", bestx / 2, bestp);
  }

  return 0;
}

