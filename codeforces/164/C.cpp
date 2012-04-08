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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

const int MAX_V = 2010;

struct e_t { int to, cap, cst, rev; };

int V, S, T;

vector<e_t> adj[MAX_V];
int pot[MAX_V], dst[MAX_V], prvv[MAX_V], prve[MAX_V];

pair<int, int> add_edge(int i, int j, int cap, int cst) {
  pair<int, int> ret = mp(i, adj[i].size());

  adj[i].push_back((e_t){j, cap, cst, adj[j].size()});
  adj[j].push_back((e_t){i, 0, -cst, adj[i].size() - 1});

  return ret;
}

pair<int, int> min_cost_flow(int req = INT_MAX) {
  int flow = 0, cost = 0;
  memset(pot, 0, sizeof(pot));

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

      rep (i, adj[v].size()) {
        e_t &e = adj[v][i];
        int w = e.to, td = dst[v] + e.cst + pot[v] - pot[w];
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




int N, K;
int bgn[1010], end[1010], prf[1010];
pair<int, int> edg[1010];

int main() {
  while (2 == scanf("%d%d", &N, &K)) {
    map<int, int> shr;
    rep (i, N) {
      scanf("%d%d%d", &bgn[i], &end[i], &prf[i]);
      end[i] += bgn[i];
      shr[bgn[i]] = shr[end[i]] = 0;
    }
    V = 0;
    tr (shr, ite) ite->second = V++;
    S = 0;
    T = V - 1;

    rep (v, V) adj[v].clear();
    rep (v, V - 1) add_edge(v, v + 1, K, 0);
    rep (i, N) edg[i] = add_edge(shr[bgn[i]], shr[end[i]], 1, -prf[i]);

    pair<int, int> f = min_cost_flow(K);
    // fprintf(stderr, "%d %d\n", f.first, f.second);
    rep (i, N) {
      int x;
      if (adj[edg[i].first][edg[i].second].cap == 0) x = 1;
      else x = 0;
      printf("%d%c", x, i == N - 1 ? '\n' : ' ');
    }
  }

  return 0;
}

