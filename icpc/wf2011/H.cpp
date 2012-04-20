#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <climits>
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

int V;
vector<int> adj[1000010], eid[1000010];
vector<int> chi[1000010];

int prenum[1000010], lowlink[1000010], times;

int saiki(int v, int prve) {
  if (prenum[v] != -1) return prenum[v];
  prenum[v] = lowlink[v] = times++;

  rep (i, adj[v].size()) {
    int w = adj[v][i];
    int e = eid[v][i];
    if (e == prve) continue;
    if (prenum[w] == -1) chi[v].pb(w);
    lowlink[v] = min(saiki(w, e), lowlink[v]);
  }
  return lowlink[v];
}

int articulation[1000010];

void connection() {
  memset(prenum, -1, sizeof(prenum));
  rep (v, V) chi[v].clear();
  times = 0;

  rep (v, V) {
    articulation[v] = (prenum[v] == -1 ? -1 : 0);
    
    if (prenum[v] == -1) saiki(v, -1);
    
    rep (i, chi[v].size()) {
      int w = chi[v][i];
      if (lowlink[w] >= prenum[v]) articulation[v]++;
    }
  }
}


bool done[1000010];
vector<int> ar;

int dfs(int v) {
  if (articulation[v] > 0) {
    ar.pb(v);
    return 0; 
  }

  if (done[v]) return 0;
  done[v] = true;

  int r = 1;
  rep (i, adj[v].size()) r += dfs(adj[v][i]);
  return r;
}


int S[1000010], T[1000010];

int main() {
  for (int ca = 1;; ++ca) {
    int E;
    scanf("%d", &E);
    if (E == 0) return 0;

    V = 0;
    rep (i, E) {
      scanf("%d%d", &S[i], &T[i]);
      --S[i];
      --T[i];
      V = max(V, max(S[i], T[i]) + 1);
    }
    
    rep (v, V) {
      adj[v].clear();
      eid[v].clear();
    }

    rep (i, E) {
      int s = S[i], t = T[i];
      adj[s].pb(t); eid[s].pb(i);
      adj[t].pb(s); eid[t].pb(i);
    }

    connection();

    int ans_c = 0;
    ll ans_p = 1;

    memset(done, 0, sizeof(done));
    rep (v, V) {
      // printf("%d: %d\n", v + 1, articulation[v]);
      if (articulation[v] > 0 || done[v]) continue;
      ar.clear();
      int cc = dfs(v);
      sort(ar.begin(), ar.end());
      ar.erase(unique(ar.begin(), ar.end()), ar.end());
      int nar = ar.size();
      // printf("%d: %d %d\n", v + 1, cc, nar);
      
      if (nar >= 2) continue;
      else if (nar == 0) {  // very special!!!
        ans_c = 2;
        ans_p = V * ll(V - 1) / 2;
      } else {
        ++ans_c;
        ans_p *= cc;
      }
    }

    cout << "Case " << ca << ": " << ans_c << " " << ans_p << endl;
  }
}
