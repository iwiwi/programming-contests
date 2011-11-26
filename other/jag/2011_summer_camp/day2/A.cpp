#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>
#include <climits>
#include <queue>
#include <cassert>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair
#define pb push_back
#define iter(c) __typeof((c).begin())

typedef long long ll;

const int MAX_V = 6010;



struct e_t { int to, cap, cst, rev; };

int V, S, T;

vector<e_t> adj[MAX_V];
int pot[MAX_V], dst[MAX_V], prvv[MAX_V], prve[MAX_V];

void add_edge(int i, int j, int cap, int cst) {
  if (i == j) return;
  adj[i].push_back((e_t){j, cap, cst, adj[j].size()});
  adj[j].push_back((e_t){i, 0, -cst, adj[i].size() - 1});
}

pair<int, int> min_cost_flow(int req = INT_MAX) {
  int flow = 0, cost = 0;
  memset(pot, 0, sizeof(pot));

  // コスト負の辺が無ければこの下は不要
  bool up;
  do {
    up = false;
    rep (v, V) rep (i, adj[v].size()) {
      if (adj[v][i].cap == 0) continue;
      int c = pot[v] + adj[v][i].cst, w = adj[v][i].to;
      if (c < pot[w]) {
        pot[w] = c;
        up = true;
      }
    }
  } while (up);

  while (flow < req) {
    fill(dst, dst + V, INT_MAX);
    priority_queue<pair<int, int> > que;
    que.push(make_pair(0, S));
    dst[S] = 0;
    while (!que.empty()) {
      int d = -que.top().first;
      int v = que.top().second;
      que.pop();
      if (d > dst[v]) continue;
      //printf(" v = %d, deg(v) = %d\n", v, (int)adj[v].size());

      rep (i, adj[v].size()) {
        e_t &e = adj[v][i];
        int w = e.to, td = dst[v] + e.cst + pot[v] - pot[w];
        // printf(" %d <- %d : %d -> %d, %d\n", w, v, dst[w], td, e.cap);
        if (e.cap && td < dst[w]) {
          que.push(make_pair(-td, w));
          dst[w] = td;
          prvv[w] = v;
          prve[w] = i;
        }
      }
    }
    if (dst[T] == INT_MAX) break;
    rep (v, V) pot[v] += dst[v];

    int f = req - flow, c = 0;
    for (int v = T; v != S; v = prvv[v]) {
      f = min(f, adj[prvv[v]][prve[v]].cap);
      c += adj[prvv[v]][prve[v]].cst;
    }
    flow += f;
    cost += f * c;
    for (int v = T; v != S; v = prvv[v]) {
      e_t &e = adj[prvv[v]][prve[v]];
      e.cap -= f;
      adj[e.to][e.rev].cap += f;
    }
  }

  return make_pair(flow, cost);
}




pair<int, pair<int, int> > mog[3010];

int main() {
  int N, V, Xl, Xr;
  while (4 == scanf("%d%d%d%d", &N, &V, &Xl, &Xr)) {
    rep (i, N) {
      int x, t, p;
      scanf("%d%d%d", &x, &t, &p);
      mog[i] = mp(t, mp(x, p));
    }

    mog[N++] = mp(0, mp(Xl, 0));
    mog[N++] = mp(0, mp(Xr, 0));
    sort(mog, mog + N);

    ::V = N * 2 + 2;
    S = N * 2;
    T = N * 2 + 1;
    rep (i, ::V) adj[i].clear();

    add_edge(S, 0 * 2, 1, 0);
    add_edge(S, 1 * 2, 1, 0);
    rep (j, N) rep (i, j) {  // i -> j
      ll dx = abs(mog[j].second.first - mog[i].second.first);
      ll dt = mog[j].first - mog[i].first;
      if (dt * V < dx) continue;
      add_edge(i * 2 + 1, j * 2, 1, 0);
    }
    rep (i, N) {
      add_edge(i * 2, i * 2 + 1, 1, -mog[i].second.second);
      add_edge(i * 2 + 1, T, 1, 0);
    }

    printf("%d\n", -min_cost_flow(2).second);
  }

  return 0;
}
