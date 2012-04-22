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


const int MAX_V = 20010;

struct e_t {
  int to;
  double cap;
  int rev;
};

int V, S, T;
vector<e_t> adj[MAX_V];

int lev[MAX_V], done[MAX_V];

void add_edge(int i, int j, double c) {
  adj[i].push_back((e_t){j, c, adj[j].size()});
  adj[j].push_back((e_t){i, 0, adj[i].size() - 1});
}

bool levelize() {
  memset(lev, -1, sizeof(lev));
  queue<int> que;
  lev[S] = 0;
  que.push(S);
  while (!que.empty()) {
    int v = que.front(); que.pop();
    rep (i, adj[v].size()) {
      e_t &e = adj[v][i];
      if (!e.cap || lev[e.to] != -1) continue;
      lev[e.to] = lev[v] + 1;
      que.push(e.to);
    }
  }
  return lev[T] != -1;
}

double augment(int v, double f) {
  if (v == T || !f) return f;
  for (; done[v] < (int)adj[v].size(); done[v]++) {
    e_t &e = adj[v][done[v]];
    if (lev[e.to] <= lev[v]) continue;
    double t = augment(e.to, min(f, e.cap));
    if (t > 0) {
      e.cap -= t;
      adj[e.to][e.rev].cap += t;
      return t;
    }
  }
  return 0;
}

double max_flow() {
  double f = 0, t;
  while (levelize()) {
    memset(done, 0, sizeof(done));
    while (0 < (t = augment(S, 1E30))) f += t;
  }
  return f;
}



int N, H;
int B[110];
int C[110][110];

bool doit(double x) {
  V = N + 2;
  S = N;
  T = N + 1;
  rep (v, V) adj[v].clear();

  double mc = 0.0;
  rep (i, N) {
    double b = B[i] - x;
    if (b > 0) {
      add_edge(i, T, b);
    } else {
      mc += b;
      add_edge(S, i, -b);
    }
  }
  rep (i, N) rep (j, N) if (i != j) add_edge(i, j, C[i][j]);
  mc += max_flow();
  // printf("mc = %f\n", mc);

  return mc < 0.0;
}

bool vis[110];
void dfs(int v) {
  if (vis[v]) return;
  vis[v] = true;
  rep (i, adj[v].size()) if (adj[v][i].cap) dfs(adj[v][i].to);
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d", &N, &H);
    if (N == 0) return 0;

    rep (i, N) scanf("%d", &B[i]);
    rep (i, N) rep (j, N) scanf("%d", &C[i][j]);

    double lb = 0.0, ub = 1E10;
    rep (iter, 100) {
      double x = (lb + ub) / 2;
      if (doit(x)) ub = x;
      else lb = x;
    }

    doit(ub);
    memset(vis, 0, sizeof(vis));
    dfs(S);
    int c = count(vis, vis + N, true);
    printf("Case %d:\n", ca);
    rep (i, N) printf("%.10f%c", vis[i] ? H / double(c) : 0.0, i + 1 == N ? '\n' : ' ');
  }

  return 0;
}

