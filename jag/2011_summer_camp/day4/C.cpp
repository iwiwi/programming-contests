#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <utility>
#include <queue>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

const ll INF = 1LL << 60;

/*
 * SHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

int N, M, L;
int K[2010], B[100010];
ll bsum[100010];

ll dp[2010][2010];

ll cost(int from_k, int to_k) {
  return (bsum[to_k + 1] - bsum[from_k]) / L;
}


int main() {
  while (3 == scanf("%d%d%d", &N, &M, &L)) {
    rep (i, N) { scanf("%d", K + i); --K[i]; }
    sort(K, K + N);

    rep (j, M) scanf("%d", B + j);
    bsum[0] = 0;
    rep (j, M) bsum[j + 1] = bsum[j] + B[j];

    // for (int j = 0; j <= M; ++j) printf("%lld\n", bsum[j]);

    dp[1][0] = cost(K[0], K[1]);
    for (int i = 2; i < N; ++i) {
      for (int j = 0; j < i; ++j) dp[i][j] = INF;

      for (int j = 0; j < i - 1; ++j) {
        dp[i][j]     = min(dp[i][j]    , dp[i - 1][j] + cost(K[i - 1], K[i]));
        dp[i][i - 1] = min(dp[i][i - 1], dp[i - 1][j] + cost(K[j],     K[i]));
      }
    }
    ll ans = dp[N - 1][N - 2] + cost(K[N - 2], K[N - 1]);
    printf("%lld\n", ans);
  }
  return 0;
}
