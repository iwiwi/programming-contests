#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

ll dp[30][110];
vector<int> adj[110];
bool F[110];

int main() {
  int T;
  scanf("%d", &T);
  rep (ca, T) {
    int N;
    scanf("%d", &N);
    rep (i, N) adj[i].clear();

    map<int, int> name2id;
    rep (i, N) {
      int name, a, b, c, f;
      scanf("%d%d%d%d%d", &name, &a, &b, &c, &f);
      name2id[name] = i;
      adj[i].pb(a);
      adj[i].pb(b);
      adj[i].pb(c);
      F[i] = f == 1;
    }
    rep (i, N) rep (j, 3) adj[i][j] = name2id[adj[i][j]];

    int L;
    scanf("%d", &L);

    memset(dp, 0, sizeof(dp));
    dp[0][name2id[1]] = 1;
    rep (l, L) rep (i, N) rep (j, 3) dp[l + 1][adj[i][j]] += dp[l][i];

    ll ans = 0;
    rep (i, N) if (F[i]) ans += dp[L][i];
    cout << ans << endl;
  }

  return 0;
}
