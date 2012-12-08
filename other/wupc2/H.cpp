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

const int MOD = 1000000007;

int N, M, K;
pair<int, int> I[210];

int dp[2][410][410];

int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    map<int, int> ma;
    ma[1] = ma[N + 1] = 0;
    rep (i, M) {
      scanf("%d%d", &I[i].first, &I[i].second);
      ++I[i].second;
      ma[I[i].first] = ma[I[i].second] = 0;
    }

    K = 0;
    tr (ma, ite) ite->second = K++;

    rep (i, M) {
      I[i].first  = ma[I[i].first];
      I[i].second = ma[I[i].second];
    }
    sort(I, I + M);

    memset(dp, 0, sizeof(dp));
    int prv = 0, nxt = 1;
    dp[prv][0][0] = 1;

    rep (i, M) {
      int l = I[i].first, r = I[i].second;

      // Don't use
      rep (a, K) rep (b, K) dp[nxt][a][b] = dp[prv][a][b];

      // Use
      for (int a = l; a < K; ++a) {
        for (int b = a; b < K; ++b) {
          if (r <= a) {
            (dp[nxt][a][b] += dp[prv][a][b]) %= MOD;
          } else if (r <= b) {
            (dp[nxt][r][b] += dp[prv][a][b]) %= MOD;
          } else {
            (dp[nxt][b][r] += dp[prv][a][b]) %= MOD;
          }
        }
      }

      swap(prv, nxt);
    }

    printf("%d\n", dp[prv][K - 1][K - 1]);
  }

  return 0;
}

