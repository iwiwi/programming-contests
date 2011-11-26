#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define pb push_back

const int MAX_V = 510;

struct e_t {
  int to, cap;//, rev;
  e_t *rev;

  e_t(int t, int c) : to(t), cap(c) {}
};

vector<e_t*> adj[MAX_V];
bool vis[MAX_V];

void add_edge(int i, int j) {
  adj[i].pb(new e_t(j, 1));
  adj[j].pb(new e_t(i, 1));
  adj[i].back()->rev = adj[j].back();
  adj[j].back()->rev = adj[i].back();
}

bool search(int v, int t) {
  if (v == t) return true;

  vis[v] = true;
  rep (i, adj[v].size()) {
    e_t &e = *adj[v][i];
    if (vis[e.to] || e.cap == 0) continue;
    if (search(e.to, t)) {
      --e.cap;
      ++e.rev->cap;
      return true;
    }
  }
  return false;
}

bool augment(int v, int t) {
  memset(vis, 0, sizeof(vis));
  return search(v, t);
}

int N, E, Q;

int main() {
  bool first = true;
  while (3 == scanf("%d%d%d", &N, &E, &Q)) {
    if (!first) puts("");
    else first = false;

    rep (v, N) adj[v].clear();

    rep (i, E) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a; --b;
      add_edge(a, b);
    }

    int f = 0;
    while (augment(0, N - 1)) ++f;

    rep (q, Q) {
      int m, a, b;
      scanf("%d%d%d", &m, &a, &b);
      --a; --b;
      if (m == 1) {
        add_edge(a, b);
      } else {
        int from = -1, to = -1;
        rep (i, adj[a].size()) {
          e_t *e = adj[a][i];
          if (e->to == b) {
            e_t *r = e->rev;
            if (e->cap == 0) { from = a; to = b; }
            if (r->cap == 0) { from = b; to = a; }

            adj[a].erase(remove(adj[a].begin(), adj[a].end(), e), adj[a].end());
            adj[b].erase(remove(adj[b].begin(), adj[b].end(), r), adj[b].end());
            break;
          }
        }

        // previous: 0 -> from -> to -> (N-1)
        if (from != -1) {
          if (!augment(from, to)) {
            augment(from, 0);
            augment(N - 1, to);
            --f;
          }
        }
      }

      if (augment(0, N - 1)) ++f;
      printf("%d\n", f);
    }
  }
  return 0;
}
