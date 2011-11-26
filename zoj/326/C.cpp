#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <set>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define mp make_pair

pair<int, string> dp[1 << 13];

int main() {
  int T;
  scanf("%d", &T);
  rep (ca, T) {
    int N;
    scanf("%d", &N);

    int A[20][20];
    rep (i, N) rep (j, N) scanf("%d", &A[i][j]);

    dp[0] = mp(0, "");
    rep (b, 1 << N) if (b) {
      pair<int, string> t = mp(1, "");
      rep (i, N) if (b & (1 << i)) {
        const pair<int, string> &q = dp[b - (1 << i)];
        int p = A[i][i];
        rep (j, N) if (i != j && (b & (1 << j))) p = max(p, A[j][i]);
        // printf(" p = %d\n", p);
        t = min(t, mp(-(-q.first + p), q.second + char('A' + i)));
      }
      dp[b] = t;
    }

    printf("%.2f\n", (-dp[(1 << N) - 1].first)  / 100.0);
    printf("%s\n", dp[(1 << N) - 1].second.c_str());
  }
}
