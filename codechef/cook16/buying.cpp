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

const ll INF = 1LL << 60;
const int L = 50;

int N, M, K, A[50010];
vector<int> B[30];

ll dp[2][30][L * 2 + 10];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &N, &M, &K);

    rep (k, K) B[k].clear();
    rep (i, N) {
      scanf("%d", &A[i]);
      B[A[i] % K].pb(A[i]);
    }

    sort(A, A + N);
    int piv = A[M - 1];
    ll greedy = accumulate(A, A + M, 0LL);
    int crr = 0, nxt = 1;
    rep (k, K) for (int l = -L; l <= L; ++l) dp[crr][k][L + l] = INF;
    dp[crr][greedy % K][L + 0] = greedy;

    rep (k, K) {
      vector<int> &b = B[k];
      int n = b.size();
      sort(all(b));
      int t = lower_bound(all(b), piv) - b.begin();
      if (t < n && b[t] == piv) t += count(A, A + M, piv);

      rep (fk, K) for (int fl = -L; fl <= L; ++fl) dp[nxt][fk][L + fl] = dp[crr][fk][L + fl];

      rep (fk, K) {
        for (int fl = -L; fl <= L; ++fl) {
          // Decrease
          {
            ll ds = 0;
            int tk = fk;
            for (int dl = 1; dl <= L && t - dl >= 0 && fl - dl >= -L; ++dl) {
              ds += b[t - dl];
              tk = (tk - k + K) % K;
              dp[nxt][tk][L + fl - dl] = min(dp[nxt][tk][L + fl - dl], dp[crr][fk][L + fl] - ds);
            }
          }
          // Increase
          {
            ll ds = 0;
            int tk = fk;
            for (int dl = 1; dl <= L && t + dl <= n && fl + dl <= L; ++dl) {
              ds += b[t + dl - 1];
              tk = (tk + k) % K;
              dp[nxt][tk][L + fl + dl] = min(dp[nxt][tk][L + fl + dl], dp[crr][fk][L + fl] + ds);
            }
          }
        }
      }

      swap(crr, nxt);
    }

    ll ans = dp[crr][0][L + 0];
    if (ans > INF / 10) puts("-1");
    else printf("%lld\n", ans);
  }

  return 0;
}

