#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int INF = 987654321;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)

char A[1000010];
int N;

int dp[2][2][10][10];

bool is_valid(int le, int ri) {
  return le != 4 && ri != 4 && le % 3 <= ri % 3;
  
}

int main() {
  freopen("B.txt", "r", stdin);

  for (;;) {
    scanf("%s", A);
    N = strlen(A);
    if (A[0] == '#') return 0;

    int crr = 0, nxt = 1;
    rep (le, 9) rep (ri, 9) {
      dp[crr][0][le][ri] = dp[crr][1][le][ri] = is_valid(le, ri) ? 0 : INF;
    }

    rep (i, N) {
      int t = (A[i] - '0') - 1;
      
      rep (le, 9) rep (ri, 9) {
        dp[nxt][0][le][ri] = dp[nxt][1][le][ri] = INF;
      }

      // left
      rep (le, 9) rep (ri, 9) {
        if (is_valid(t, ri)) {
          dp[nxt][0][t][ri] = min(dp[nxt][0][t][ri], dp[crr][0][le][ri] + 1);
          dp[nxt][0][t][ri] = min(dp[nxt][0][t][ri], dp[crr][1][le][ri]);
        }
        
        // right step
        if (is_valid(le, t)) {
          dp[nxt][1][le][t] = min(dp[nxt][1][le][t], dp[crr][0][le][ri]);
          dp[nxt][1][le][t] = min(dp[nxt][1][le][t], dp[crr][1][le][ri] + 1);
        }
      }
      
      swap(nxt, crr);
    }

    int ans = INF;
    rep (le, 9) rep (ri, 9) {
      if (is_valid(le, ri)) {
        ans = min(ans, dp[crr][0][le][ri]);
        ans = min(ans, dp[crr][1][le][ri]);
      }
    }
    printf("%d\n", ans);
  }
}
