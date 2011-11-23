#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <map>
#include <climits>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second

const int INF = 87654321;

int N, M;
int F[60], H[60];
int adj[2][60][60];
int tmp[2][60][60];

int dp[60][60];

vector<int> minc(int v, int g, const vector<int> &ws) {
  int n = ws.size();
  vector<int> res(n, INF);
  rep (i, n) res[i] = adj[g][v][ws[i]];
  rep (i, n) rep (j, n) res[i] = min(res[i], res[j] + tmp[g][ws[j]][ws[i]]);
  return res;
}

int main() {
  for (;;) {
    scanf("%d%d", &N, &M);
    if (N == 0 && M == 0) return 0;

    F[0] = F[N - 1] = 0;
    H[0] = 0;
    H[N - 1] = 1000;
    for (int v = 1; v < N - 1; ++v) {
      scanf("%d%d", &F[v], &H[v]);
    }
    
    rep (v, N) rep (w, N) {
      adj[0][v][w] = adj[1][v][w] = v == w ? 0 : INF;
    }
    
    rep (i, M) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      --a; --b;
      if (H[a] <= H[b]) adj[0][a][b] = c;
      if (H[b] <= H[a]) adj[1][b][a] = c;
    }

    rep (v, N) rep (w, N) dp[v][w] = INF;
    dp[0][0] = 0;

    for (int th = 1; th <= 1000; ++th) {
      vector<int> vs;
      rep (v, N) if (H[v] == th) vs.pb(v);
      if (vs.empty()) continue;

      rep (b, 1 << vs.size()) {
	vector<int> ws;
	rep (i, vs.size()) if (b & (1 << i)) ws.pb(vs[i]);
	int n = ws.size();
	int f = 0;
	rep (i, n) f += F[ws[i]];

	// printf("%d: ", th); rep (i, ws.size()) printf(" %d", ws[i]); puts("");

	rep (g, 2) rep (i, n) rep (j, n) tmp[g][ws[i]][ws[j]] = adj[g][ws[i]][ws[j]];
	rep (g, 2) rep (k, n) rep (i, n) rep (j, n) {
	  int tx = ws[k], tv = ws[i], tw = ws[j];
	  tmp[g][tv][tw] = min(tmp[g][tv][tw], tmp[g][tv][tx] + tmp[g][tx][tw]);
	}
	/*
	rep (g, 2) {
	  rep (i, n) { rep (j, n) printf(" %d", tmp[g][ws[i]][ws[j]]); puts(""); }
	  puts("");
	}
	*/
	
	rep (v, N) rep (w, N) if (H[v] < th && H[w] < th) {
	  int c = dp[v][w];
	  if (c == INF) continue;
	  vector<int> cv = minc(v, 0, ws);
	  vector<int> cw = minc(w, 1, ws);
	  cv.resize(n + 1, 0);
	  cw.resize(n + 1, 0);
	  rep (tvi, n + 1) rep (twi, n + 1) {
	    int tv = tvi == n ? v : ws[tvi];
	    int tw = twi == n ? w : ws[twi];
	    int tc = c + f + cv[tvi] + cw[twi];
	    if (tc < dp[tv][tw]) {
	      dp[tv][tw] = tc;
	      // printf(" %d %d -> %d %d: %d\n", v, w, tv, tw, dp[tv][tw]);
	    }
	  }
	}
      }
    }

    int ans = dp[N - 1][N - 1];
    if (ans >= INF) puts("-1");
    else printf("%d\n", ans);
  }
}
