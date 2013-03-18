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

int N, Q, T;
int A[310], R[310];
int par[310], chi[310];

int dp[1000010];
bool loop;

int saiki(int v) {
  if (R[v] != -1) {
    loop |= (R[v] == -2);
    return R[v];
  }

  if (par[v] == -1) {
    return R[v] = A[v];
  } else {
    R[v] = -2;
    return R[v] = A[v] + saiki(par[v]);
  }
}

int main() {
  while (3 == scanf("%d%d%d", &N, &Q, &T)) {
    rep (i, N) scanf("%d", &A[i]);

    memset(par, -1, sizeof(par));
    memset(chi, -1, sizeof(chi));
    rep (i, Q) {
      int b, c;
      scanf("%d%d", &b, &c);
      --b;
      --c;
      chi[b] = c;
      par[c] = b;
    }

    memset(R, -1, sizeof(R));
    loop = false;
    rep (i, N) saiki(i);
    if (loop) {
      puts("0");
      continue;
    }

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    rep (i, N) {
      int r = R[i];
      if (chi[i] != -1) T = max(T - r, -1);
      for (int x = 0; x + r <= T; ++x) (dp[x + r] += dp[x]) %= MOD;
    }

    printf("%d\n", T >= 0 ? dp[T] : 0);
  }

  return 0;
}

