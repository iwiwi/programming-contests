#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <map>

using namespace std;

const int INF = 987654321;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back
#define mp make_pair

int N, M;
vector<int> adj[100010];
vector<int> dst[100010];
vector<int> cst[100010];

pair<int, int> pot[100010];

int main() {
  freopen("H.txt", "r", stdin);

  for (;;) {
    scanf("%d%d", &N, &M);
    if (N == 0 && M == 0) return 0;

    rep (i, N) {
      adj[i].clear();
      dst[i].clear();
      cst[i].clear();
    }
    
    rep (i, M) {
      int v, w, d, c;
      scanf("%d%d%d%d", &v, &w, &d, &c);
      --v;
      --w;
      adj[v].pb(w); dst[v].pb(d); cst[v].pb(c);
      adj[w].pb(v); dst[w].pb(d); cst[w].pb(c);
    }

    multimap<pair<int, int>, int> que;
    rep (i, N) pot[i] = make_pair(INF, 0);
    int ans = 0;

    que.insert(mp(mp(0, 0), 0));
    pot[0] = mp(0, 0);
    while (!que.empty()) {
      int v = que.begin()->second;
      pair<int, int> p = que.begin()->first;
      que.erase(que.begin());
      if (p > pot[v]) continue;

      // printf("v=%d %d\n", v, p.second);
      
      ans += p.second;  // use this edge !!
      
      rep (i, adj[v].size()) {
        int tv = adj[v][i];
        // printf(" tv=%d\n", tv);
        pair<int, int> tp = mp(p.first + dst[v][i], cst[v][i]);
        if (tp < pot[tv]) {
          que.insert(mp(tp, tv));
          pot[tv] = tp;
        }
      }
    }

    printf("%d\n", ans);
  }
}
