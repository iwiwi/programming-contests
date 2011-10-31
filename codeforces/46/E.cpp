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
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

const ll INF = 987654321987654321LL;

int N, M;
int A[1510][1510];

ll dp[2][1510];


int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    rep (i, N) rep (j, M) scanf("%d", &A[i][j]);

    memset(dp, 0, sizeof(dp));
    ll *prv = dp[0], *nxt = dp[1];
    rep (i, N) {
      if (i % 2 == 0) {
        ll p = prv[0], s = 0;
        nxt[0] = -INF;
        for (int j = 1; j <= M; ++j) {
          s += A[i][j - 1];
          nxt[j] = s + p;
          p = max(p, prv[j]);
        }
      }
      else {
        ll p = -INF, s = accumulate(A[i], A[i] + M, 0);
        for (int j = M; j >= 1; --j) {
          nxt[j] = s + p;
          s -= A[i][j - 1];
          p = max(p, prv[j]);
        }
        nxt[0] = -INF;
      }
      // for (int j = 0; j <= M; ++j) printf("%lld ", nxt[j]); puts("");
      swap(prv, nxt);
    }

    cout << *max_element(prv, prv + M + 1) << endl;
  }

  return 0;
}

