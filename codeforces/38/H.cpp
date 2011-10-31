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

const int INF = 987654321;

int N, M, K;
int G1, G2, S1, S2;
ll adj[60][60];

ll dis[60][60];

ll dp[60][60], nxt[60][60];

ll solve(ll bst, ll wst) {
  // printf("# %lld %lld\n", bst, wst);

  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  
  rep (i, N) {
    bool g = false, s = false, b = false;
    if (dis[i][0] == bst) {
      if (dis[i][K - 1] == wst) return 0;
      g = true;
      s = b = false;
    }
    else if (dis[i][K - 1] == wst) {
      g = s = false;
      b = true;
    }
    else {
      g |= dis[i][0] < bst;
      b |= dis[i][K - 1] > wst;
      rep (j, K) s |= bst < dis[i][j] && dis[i][j] < wst;
    }

    memset(nxt, 0, sizeof(nxt));
    rep (j, N) rep (k, N) {
      if (g) nxt[j + 1][k] += dp[j][k];
      if (s) nxt[j][k + 1] += dp[j][k];
      if (b) nxt[j][k] += dp[j][k];
    }

    memcpy(dp, nxt, sizeof(dp));
  }

  ll res = 0;
  for (int g = G1; g <= G2; ++g) {
    for (int s = S1; s <= S2; ++s) {
      res += dp[g][s];
    }
  }
  return res;
}

int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    rep (i, N) rep (j, N) adj[i][j] = i == j ? 0 : INF;
    rep (i, M) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      --a;
      --b;
      adj[a][b] = adj[b][a] = min(adj[a][b], (ll)c);
      // printf(" %d %d %d\n", a, b, c);
    }
    rep (k, N) rep (i, N) rep (j, N) adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

    scanf("%d%d%d%d", &G1, &G2, &S1, &S2);

    K = N - 1;
    rep (i, N) {
      sort(adj[i], adj[i] + N);
      rep (j, K) {
        dis[i][j] = adj[i][j + 1] * (ll)N + i;
        // printf("%lld ", dis[i][j]);
      }
      // puts("");
    }

    ll bst[60], wst[60];
    rep (i, N) {
      bst[i] = dis[i][0];
      wst[i] = dis[i][K - 1];
    }
    sort(bst, bst + N);
    sort(wst, wst + N);

    ll ans = 0;
    rep (i, N) rep (j, N) {
      ans += solve(bst[i], wst[j]);
    }
    cout << ans << endl;
  }

  
  return 0;
}

