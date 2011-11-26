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

typedef long long ll;

const ll INF = 987654321987654321LL;

int N, P, Q, D;
int d[1010], a[1010], b[1010];

ll dp[2][100010];

int main() {
  for (;;) {
    scanf("%d%d%d%d", &N, &P, &Q, &D);
    if (N == 0 && P == 0 && Q == 0 && D == 0) return 0;

    int M = max(P, Q);

    d[0] = 0;
    for (int i = 1; i <= N; ++i) scanf("%d%d%d", d + i, a + i, b + i);

    memset(dp, 0, sizeof(dp));
    ll *prv = dp[0], *nxt = dp[1];
    prv[0] = 0;
    for (int q = 1; q <= M; ++q) prv[q] = INF;

    for (int i = 1; i <= N; ++i) {
      ll td = d[i] - d[i - 1];

      ll crr = INF;
      for (int q = 0; q <= M; ++q) {
        prv[q] += q * (ll)q * td;
        crr = min(crr + a[i], prv[q] + b[i]);
        nxt[q] = min(prv[q], crr);
      }

      swap(prv, nxt);
    }

    ll ans = INF;
    for (int q = P; q <= M; ++q) {
      ans = min(ans, prv[q] + q * (ll)q * (D - d[N]) - q * Q);
    }
    cout << ans << endl;
  }

  return 0;
}

