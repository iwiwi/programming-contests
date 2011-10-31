#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>
#include <climits>
#include <queue>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair
#define pb push_back
#define iter(c) __typeof((c).begin())

const int MAX_V = 3010;

struct e_t { int to, cap, cst, rev; };

int V, S, T;

vector<e_t> adj[MAX_V];
int pot[MAX_V], dst[MAX_V], prvv[MAX_V], prve[MAX_V];

void add_edge(int i, int j, int cap, int cst) {
  adj[i].push_back((e_t){j, cap, cst, adj[j].size()});
  adj[j].push_back((e_t){i, 0, -cst, adj[i].size() - 1});
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



map<int, int> ma;
int getvid(int a) {
  if (ma.count(a)) return ma[a];
  int vid = V++;
  ma[a] = vid;
  adj[vid].clear();
  // printf("%d, vid = %d\n", a, vid);
  add_edge(vid, T, 1, 0);
  return vid;
}

int main() {
  int N;
  cin >> N;
  {
    S = 0;
    T = 1;
    V = 2 + N;
    rep (i, V) adj[i].clear();

    int pad = 0;

    rep (i, N) {
      int a, b;
      cin >> a >> b;

      pad += a + b;

      add_edge(S, 2 + i, 1, 0);

      add_edge(2 + i, T, 1, a + b);
      add_edge(2 + i, getvid(a), 1, a);
      add_edge(2 + i, getvid(b), 1, b);
    }

    int res =  -min_cost_flow(N).second;
    cout << pad + res << endl;
    // printf("%d\n", pad + res);
  }

  return 0;
}
