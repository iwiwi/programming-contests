#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <climits>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair
#define pb push_back

const int MAX_V = 1010;
struct e_t {
  int to, cap, cst, rev;
};
int V, S, T;

vector<e_t> adj[MAX_V];
int pot[MAX_V], dst[MAX_V], prvv[MAX_V], prve[MAX_V];

void add_edge(int i, int j, int cap, int cst) {
  adj[i].pb((e_t){j, cap, +cst, adj[j].size()});
  adj[j].pb((e_t){i,   0, -cst, adj[i].size() - 1});
}

pair<int, int> min_cost_flow() {
  int flow = 0, cost = 0;
  memset(pot, 0, sizeof(pot));

  for (;;) {
    fill(dst, dst + V, INT_MAX);
    priority_queue<pair<int, int> > que;
    que.push(mp(0, S));
    dst[S] = 0;
    while (!que.empty()) {
      int v = que.top().second; que.pop();
      rep (i, adj[v].size()) {
	e_t &e = adj[v][i];
	int w = e.to;
	int td = dst[v] + e.cst + pot[v] - pot[w];
	if (e.cap && td < dst[w]) {
	  que.push(mp(-td, w));
	  dst[w] = td;
	  prvv[w] = v;
	  prve[w] = i;
	}
      }
    }
    if (dst[T] == INT_MAX) break;
    rep (v, V) pot[v] += dst[v];

    int f = INT_MAX;
    for (int v = T; v != S; v = prvv[v]) {
      f = min(f, adj[prvv[v]][prve[v]].cap);
    }
    for (int v = T; v != S; v = prvv[v]) {
      e_t &e = adj[prvv[v]][prve[v]];
      e.cap -= f;
      adj[e.to][e.rev].cap += f;
    }
    flow += f;
    cost += f * pot[T];
  }
  return mp(flow, cost);
}

int H, W;
int HN[60], WN[60];
double A[60][60];

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d", &H, &W);
    if (H == 0 && W == 0) return 0;

    rep (i, H) scanf("%d", &HN[i]);
    rep (j, W) scanf("%d", &WN[j]);
    rep (i, H) rep (j, W) scanf("%lf", &A[i][j]);

    map<int, int> ans;
    for (int s = -1; s <= 1; ++s) {
      V = H + W + 2;
      S = H + W;
      T = H + W + 1;
      rep (v, V) adj[v].clear();
      
      rep (i, H) add_edge(S    , i, HN[i], 0);
      rep (j, W) add_edge(H + j, T, WN[j], 0);

      rep (i, H) rep (j, W) {
	if (A[i][j] < 0) continue;
	int c = 100 + s * (int)round(A[i][j] * 100);
	add_edge(i, H + j, 200, c);
      }

      pair<int, int> f = min_cost_flow();
      // printf("%d %d\n", f.first, f.second);
      int c = f.second;
      c -= 100 * f.first;
      c *= s;
      ans[s] = c;
    }

    printf("Problem %d: %.2f to %.2f\n", ca, ans[1] / 100.0, ans[-1] / 100.0);
  }
}
