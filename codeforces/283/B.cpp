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

int N;
int A[200010];

ll dp[2][200010];

void doit(int x, int t) {
  vector<pair<int, int> > stk;
  while (1 < x && x <= N && dp[t][x] == 0) {
    dp[t][x] = -1;
    stk.pb(mp(x, t));

    x = t == 0 ? x + A[x] : x - A[x];
    t = 1 - t;
  }

  if (x == 1 || (1 < x && x <= N && dp[t][x] == -1)) return;  // Loop!
  else {
    ll y = 0;
    if (1 < x && x <= N) y = dp[t][x];

    reverse(all(stk));
    rep (i, stk.size()) {
      y += A[stk[i].first];
      dp[stk[i].second][stk[i].first] = y;
      // printf(" %d %d: %lld\n", stk[i].second, stk[i].first, y);
    }
  }
}

int main() {
  while (1 == scanf("%d", &N)) {
    for (int i = 2; i <= N; ++i) scanf("%d", &A[i]);
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i < N; ++i) {
      doit(1 + i, 1);
      ll ans = dp[1][1 + i];
      if (ans != -1) ans += i;

#ifdef LOCAL
      printf("%lld\n", ans);
#else
      printf("%I64d\n", ans);
#endif
    }
  }

  return 0;
}

