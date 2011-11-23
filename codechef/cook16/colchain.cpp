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

const ll MOD = 1000000007;

int N, M;
ll dp[200010], ans;

void add(int b, int e, ll v) {  // [b, e)
  ll k = max(0, min(e - b, e - N));
  ans += k * v; ans %= MOD;

  dp[b] += v; dp[b] %= MOD;
  dp[e] -= v; dp[e] %= MOD;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &M);

    memset(dp, 0, sizeof(dp));
    ans = 0;

    add(M, M + 1, 1);
    for (int k = 0; k + 1 < M; ++k) {
      int p = M - (k + 1);
      add(M + k + 1, M + k + 1 + 1, p);
    }

    ll s = 0;
    for (int i = M; i < N; ++i) {
      s += dp[i]; s %= MOD;
      add(i + 1, i + 1 + M, s);
    }

    ll f = 1;
    rep (i, M) {
      f *= i + 1; f %= MOD;
    }

    ll res = ((ans * f) % MOD + MOD) % MOD;
    cout << res << endl;
  }

  return 0;
}

