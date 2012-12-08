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

int N, M, K;
vector<pair<int, int> > adj[110];

bool loop[110];
int vis[110];

int search(int v, int p) {
  if (vis[v] == 1) return -1;
  if (vis[v] == 0) {
    loop[v] = true;
    return v;
  }

  vis[v] = 0;

  int r = -1;
  rep (i, adj[v].size()) if (adj[v][i].first != p) {
    int t = search(adj[v][i].first, v);
    if (t != -1) r = t;
  }

  vis[v] = 1;

  if (r != -1) {
    loop[v] = true;
    if (r == v) r = -1;
  }
  return r;
}

int main() {
  while (3 == scanf("%d%d%d", &N, &M, &K)) {
    rep (v, N) adj[v].clear();

    rep (i, M) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      --a;
      --b;
      adj[a].pb(mp(b, c));
      adj[b].pb(mp(a, c));
    }

    memset(loop, 0, sizeof(loop));
    memset(vis, -1, sizeof(vis));
    rep (i, N) search(i, -1);
    // rep (i, N) printf("%d ", loop[i]); puts("");

    int L = count(loop, loop + N, true);
    int T = (L == 0 ? N : N - L + 1);

    vector<int> le, te;
    rep (v, N) rep (i, adj[v].size()) {
      int w = adj[v][i].first;
      if (w < v) continue;

      if (loop[v] && loop[w]) le.pb(adj[v][i].second);
      else te.pb(adj[v][i].second);
    }

    assert((int)te.size() <= T - 1);
    te.resize(T - 1, 0);

    sort(all(le));
    sort(all(te));

    int ans = 987654321;
    for (int lc = 0; lc <= (int)le.size(); ++lc) {
      for (int tc = 0; tc <= (int)te.size(); ++tc) {
        int k = (lc >= 2 ? lc - 1 : 0) + tc + 1;
        if (k >= K) {
          ans = min(ans,
                    accumulate(le.begin(), le.begin() + lc, 0) +
                    accumulate(te.begin(), te.begin() + tc, 0));
        }
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}

