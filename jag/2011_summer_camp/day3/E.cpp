#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <climits>
using namespace std;

#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

const int MAX_V = 1010;

struct e_t { int to, cap, rev, id; };

int V, S, T;
vector<e_t> adj[MAX_V];

void add_edge(int i, int j, int id) {
  adj[i].pb((e_t){j, 1, adj[j].size(),     -1});
  adj[j].pb((e_t){i, 1, adj[i].size() - 1, id});   // rev ni ID!!!!!
}

int prvv[MAX_V], prve[MAX_V];

int max_flow() {
  int f, a;
  for (f = 0; ; f += a) {
    memset(prvv, -1, sizeof(prvv));
    queue<int> que;
    prvv[S] = -2;
    que.push(S);
    while (!que.empty() && prvv[T] == -1) {
      int j = que.front();
      que.pop();
      for (int i = 0; i < (int)adj[j].size(); ++i) {
        e_t &e = adj[j][i];
        if (prvv[e.to] == -1 && e.cap > 0) {
          prvv[e.to] = j;
          prve[e.to] = i;
          que.push(e.to);
        }
      }
    }
    if (prvv[T] == -1) return f;
    a = INT_MAX;
    for (int i = T; i != S; i = prvv[i])
      a = min(a, adj[prvv[i]][prve[i]].cap);
    for (int i = T; i != S; i = prvv[i]) {
      e_t &e = adj[prvv[i]][prve[i]];
      e.cap -= a;
      adj[i][e.rev].cap += a;
    }
  }
  return f;
}


int main() {
  int E;
  while (cin >> V >> E) {
    rep (v, V) adj[v].clear();

    int x, y;
    rep (i, E) {
      cin >> x >> y;
      --x; --y;
      add_edge(x, y, i);
    }

    cin >> S >> T;
    --S; --T;

    printf("%d\n", max_flow());

    vector<int> revs;
    rep (v, V) rep (i, adj[v].size()) {
      if (adj[v][i].id != -1 && adj[v][i].cap == 0) {
        revs.pb(adj[v][i].id);
      }
    }

    printf("%d\n", (int)revs.size());
    rep (i, revs.size()) printf("%d\n", revs[i] + 1);
  }
  return 0;
}
