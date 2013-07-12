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

int R, K[70], X[70][15], Y[70];

bool can_reduce(int l, int r, int y, int *a, int mem[60][60][50]) {
  int &t = mem[l][r][y];
  if (t != -1) return t;
  if (r - l == 1) return y == a[l];

  rep (i, R) if (Y[i] == y) {
    bool dp[15][60] = {};
    dp[0][l] = true;

    rep (k, K[i]) {
      for (int tl = l; tl < r; ++tl) {
        if (!dp[k][tl]) continue;

        for (int tr = tl + 1; tr <= r; ++tr) {
          if (mp(l, r) == mp(tl, tr)) continue;
          if (can_reduce(tl, tr, X[i][k], a, mem)) dp[k + 1][tr] = true;
        }
      }
    }
    if (dp[K[i]][r]) return (t = 1);
  }

  return (t = 0);
}

int AN, BN, A[60], B[60];
int memA[60][60][50], memB[60][60][50], mem2[60][60][60][60];

bool can_match(int al, int ar, int bl, int br) {
  int &t = mem2[al][ar][bl][br];
  if (t != -1) return t;
  rep (y, 30) {
    if (can_reduce(al, ar, y, A, memA) && can_reduce(bl, br, y, B, memB)) {
      return (t = 1);
    }
  }
  return (t = 0);
}

int main() {
  for (;;) {
    scanf("%d%d%d", &AN, &BN, &R);
    if (!(AN|BN|R)) break;

    rep (i, AN) { scanf("%d", &A[i]); A[AN + i] = --A[i]; }
    rep (i, BN) { scanf("%d", &B[i]); B[BN + i] = --B[i]; }
    rep (i, R) {
      scanf("%d", &K[i]);
      rep (j, K[i]) { scanf("%d", &X[i][j]); --X[i][j]; }
      scanf("%d", &Y[i]);
      --Y[i];
    }

    int ans = -1;
    memset(memA, -1, sizeof(memA));
    memset(memB, -1, sizeof(memB));
    memset(mem2, -1, sizeof(mem2));
    rep (as, AN) rep (bs, BN) {
      int dp[60][60];
      memset(dp, -1, sizeof(dp));
      dp[as][bs] = 0;

      for (int al = as; al < as + AN; ++al) {
        for (int bl = bs; bl < bs + BN; ++bl) {
          if (dp[al][bl] == -1) continue;

          for (int ar = al + 1; ar <= as + AN; ++ar) {
            for (int br = bl + 1; br <= bs + BN; ++br) {
              if (can_match(al, ar, bl, br)) {
                dp[ar][br] = max(dp[ar][br], dp[al][bl] + 1);
              }
            }
          }
        }
      }

      ans = max(ans, dp[as + AN][bs + BN]);
    }

    printf("%d\n", ans);
  }

  return 0;
}

