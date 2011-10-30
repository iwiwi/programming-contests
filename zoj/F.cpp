#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

bool dp[2][121][121][121];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    int prv = 0, nxt = 1;
    memset(dp, 0, sizeof(dp));
    
    int as = 0, bs = 0, cs = 0;
    dp[prv][0][0][0] = true;

    rep (i, N) {
      int ta, tb, tc;
      scanf("%d%d%d", &ta, &tb, &tc);

      as += ta;
      bs += tb;
      cs += tc;
      for (int a = 0; a <= as; ++a) {
        for (int b = 0; b <= bs; ++b) {
          for (int c = 0; c <= cs; ++c) {
            dp[nxt][a][b][c] = false;
          }
        }
      }
      
      for (int a = 0; a <= as - ta; ++a) {
        for (int b = 0; b <= bs - tb; ++b) {
          for (int c = 0; c <= cs - tc; ++c) {
            if (!dp[prv][a][b][c]) continue;
            dp[nxt][a + ta][b][c] = true;
            dp[nxt][a][b + tb][c] = true;
            dp[nxt][a][b][c + tc] = true;
          }
        }
      }

      swap(prv, nxt);
    }

    for (int s = 0; s <= 120; ++s) {
      if (dp[prv][s][s][s]) {
        printf("%d\n", s);
        goto done;
      }
    }
    puts("NO");
  done:;
  }
}
