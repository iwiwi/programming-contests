#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <map>

using namespace std;

const int INF = 987654321;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back
#define mp make_pair

int V;
vector<int> adj[2010];
int mat[2010];
bool vis[2010];

int augment(int v) {
  rep (i, adj[v].size()) {
    int w = adj[v][i];
    if (!vis[w]) {
      vis[w] = true;
      if (mat[w] < 0 || augment(mat[w])) {
        mat[v] = w;
        mat[w] = v;
        return 1;
      }
    }
  }
  return 0;
}

int bipartite_matching() {
  int res = 0;
  memset(mat, -1, sizeof(mat));
  rep (i, V) if (mat[i] == -1) {
    memset(vis, 0, sizeof(vis));
    res += augment(i);
  }
  return res;
}

int N, M, L;
ll dst[110][110];

int P[1010];
int T[1010];

int main() {
  freopen("J.txt", "r", stdin);

  for (;;) {
    scanf("%d%d%d", &N, &M, &L);
    if (N == 0 && M == 0 && L == 0) return 0;
    
    rep (i, N) rep (j, N) dst[i][j] = i == j ? 0 : INF;
    rep (i, M) {
      int u, v, d;
      scanf("%d%d%d", &u, &v, &d);
      dst[u][v] = dst[v][u] = min(dst[u][v], (ll)d);
    }

    rep (i, L) {
      scanf("%d%d", &P[i], &T[i]);
    }

    rep (k, N) rep (i, N) rep (j, N) dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
    
    V = L + L;
    rep (i, V) adj[i].clear();

    rep (i, L) {
      rep (j, L) if (i != j) {
        if (T[i] + dst[P[i]][P[j]] <= T[j]) {
          // printf("%d %d -- dst[%d][%d] = %d\n", i, j, P[i], P[j], dst[P[i]][P[j]]);
          adj[i].pb(L + j);
          adj[L + j].pb(i);
        }
      }
    }
    printf("%d\n", L - bipartite_matching());
  }
}
