#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <set>
#include <iostream>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define mp make_pair

const int INF = 987654321;

int N, M;
int dt[510][510];

char C[50010];
int X[50010], Y[50010];

// Spanning Forest
vector<int> adj[510];

// Find the edge that is deleted first in the path from |v| to |w|
int search(int p, int v, int w) {
  if (v == w) return INF;

  rep (i, adj[v].size()) {
    int tv = adj[v][i];
    if (tv == p) continue;
    int r = search(v, tv, w);
    if (r >= 0) return min(dt[v][tv], r);
  }

  return -1;
}

int main() {
  for (int ca = 1; 2 == scanf("%d%d", &N, &M); ++ca) {
    rep (i, N) rep (j, N) dt[i][j] = INF;
    rep (i, N) adj[i].clear();

    rep (i, M) {
      scanf(" %c%d%d", &C[i], &X[i], &Y[i]);
      --X[i];
      --Y[i];
      if (C[i] == 'D') {
        dt[X[i]][Y[i]] = dt[Y[i]][X[i]] = i;
      }
    }

    if (ca > 1) puts("");
    printf("Case %d:\n", ca);

    rep (i, M) {
      int x = X[i], y = Y[i];
      if (C[i] == 'I') {
        int k = search(-1, X[i], Y[i]);
        if (k < dt[x][y] && k != -1) {
          int ox = X[k], oy = Y[k];
          // printf("erase: %d %d\n", ox, oy);
          adj[ox].erase(find(adj[ox].begin(), adj[ox].end(), oy));
          adj[oy].erase(find(adj[oy].begin(), adj[oy].end(), ox));
        }
        if (k < dt[x][y]) {
          // printf("add: %d %d\n", x, y);
          adj[x].push_back(y);
          adj[y].push_back(x);
        }
      } else if (C[i] == 'Q') {
        if (search(-1, x, y) > i) puts("YES");
        else puts("NO");
      }
    }
  }
}
