#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)

const int INF = 100000000;

int N, M;
int adj[30][30];

int mem[2][20][1 << 20];

int search(int v, int s, int g) {
  if (s == 0) {
    if (v == g) return 0;
    else return INF;
  } else {
    int &m = mem[g == 0 ? 0 : 1][v][s];
    if (m != -1) return m;
    m = INF;
    rep (w, N) if (s & (1 << w)) {
      m = min(m, adj[v][w] + search(w, s - (1 << w), g));
    }
    return m;
  }
}


int main() {
  for (int ca = 1; 2 == scanf("%d%d", &N, &M); ++ca) {
    rep (i, N) rep (j, N) adj[i][j] = INF;
    rep (i, M) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      adj[a][b] = adj[b][a] = c;
    }
    rep (k, N) rep (i, N) rep (j, N) adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
    
    memset(mem, -1, sizeof(mem));

    int ans = INF;
    int f = (N - 2) / 2;
    rep (iter, 1 << (N - 2)) {
      int s = iter << 1;
      int t = ((1 << (N - 2)) - 1 - iter) << 1;
      if (__builtin_popcount(s) != f) continue;

      int fwd = INF, bwd = INF;
      rep (a, N) rep (b, N) {
	if ((s & (1 << a)) == 0) continue;
	if ((t & (1 << b)) == 0) continue;

	int ts = s - (1 << a), tt = t - (1 << b);
	int tf = search(a, ts | (1 << 0      ), 0    ) + adj[a][b] + search(b, tt | (1 << (N - 1)), N - 1);
	int tb = search(a, ts | (1 << (N - 1)), N - 1) + adj[a][b] + search(b, tt | (1 << 0)      , 0);
	fwd = min(fwd, tf);
	bwd = min(bwd, tb);
      }
      ans = min(ans, fwd + bwd);
    }

    if (N == 3) ans = adj[0][1] + adj[1][2] + adj[2][1] + adj[1][0];
    printf("Case %d: %d\n", ca, ans);
  }
}
