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
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

const int MAX_V = 100010;

const int MAX_N = 200100;
const int MAX_LOGN = 20;

int par[MAX_N], rank[MAX_N];

void init(int n) {
  for (int i = 0; i < n; i++) {
    par[i] = i;
    rank[i] = 0;
  }
}

int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}

void unite(int x, int y) {
  x = root(x);
  y = root(y);
  if (x == y) return;

  if (rank[x] < rank[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rank[x] == rank[y]) rank[x]++;
  }
}

bool find(int x, int y) {
  return root(x) == root(y);
}




int V;
vector<int> adj[MAX_V], eid[MAX_V];

vector<int> chi[MAX_V];
int prenum[MAX_V], lowlink[MAX_V], times;

int saiki(int v, int prve) {
  if (prenum[v] != -1) return prenum[v];
  prenum[v] = lowlink[v] = times++;

  for (int i = 0; i < adj[v].size(); i++) {
    int w = adj[v][i];
    int e = eid[v][i];
    if (e == prve) continue;
    if (prenum[w] == -1) chi[v].push_back(w);
    lowlink[v] = min(saiki(w, e), lowlink[v]);
  }
  return lowlink[v];
}

int articulation[MAX_V];
vector<pair<int, int> > bridge;

int connection() {
  memset(prenum, -1, sizeof(prenum));
  for (int v = 0; v < V; v++) chi[v].clear();
  times = 0;

  int res = 0;
  for (int v = 0; v < V; v++) {
    articulation[v] = (prenum[v] == -1 ? -1 : 0);

    if (prenum[v] == -1) {
      saiki(v, -1);
      res++;
    }

    for (int i = 0; i < chi[v].size(); i++) {
      int w = chi[v][i];
      if (lowlink[w] >= prenum[v]) articulation[v]++;
      if (lowlink[w] > prenum[v]) bridge.push_back(make_pair(v, w));
      else unite(v, w);  // ohhhhh
    }
  }

  return res;
}




int val[MAX_LOGN][MAX_N];
int idx[MAX_LOGN][MAX_N];

void construct_rmq(int *a, int n) {
  memcpy(val[0], a, sizeof(int) * n);
  for (int i = 0; i < n; i++) idx[0][i] = i;

  int l = 1;
  for (int k = 1; k < n; k *= 2) {
    for (int i = 0; i + k < n; i++) {
      if (val[l - 1][i] <= val[l - 1][i + k]) {
        val[l][i] = val[l - 1][i];
        idx[l][i] = idx[l - 1][i];
      }
      else {
        val[l][i] = val[l - 1][i + k];
        idx[l][i] = idx[l - 1][i + k];
      }
    }
    l++;
  }
}

int rmq(int a, int b) { // [a, b]
  int l = 31 - __builtin_clz(b - a + 1), k = 1 << l, c = b - k + 1;
  return val[l][a] <= val[l][c] ? idx[l][a] : idx[l][c];
}

int START;

int current, number;
int order[MAX_V * 2];
int level[MAX_V * 2];
int first[MAX_V];

void construct_lca(int v = START, int p = -1, int l = 0) {
  if (v == START) current = number = 0;

  number++;
  order[current] = v;
  level[current] = l;
  first[v] = current++;

  for (int j = 0; j < adj[v].size(); j++) {
    int u = adj[v][j];
    if (u == p) continue;
    construct_lca(u, v, l + 1);

    order[current] = v;
    level[current] = l;
    current++;
  }

  if (v == START) construct_rmq(level, 2 * number - 1);
}

int lca(int u, int v) {
  if (first[u] > first[v]) swap(u, v);
  return order[rmq(first[u], first[v])];
}




int main() {
  int n, m;
  while (2 == scanf("%d%d", &n, &m)) {
    rep (i, n) adj[i].clear(), eid[i].clear();

    V = n;
    rep (i, m) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a; --b;
      adj[a].pb(b); eid[a].pb(i);
      adj[b].pb(a); eid[b].pb(i);
    }

    bridge.clear();
    init(n);
    connection();

    rep (i, n) adj[i].clear();
    rep (i, bridge.size()) {
      // printf("bridge %d-%d\n", bridge[i].first, bridge[i].second);

      int v = root(bridge[i].first);
      int w = root(bridge[i].second);
      adj[v].pb(w);
      adj[w].pb(v);
    }
    START = root(0);
    construct_lca();

    int k;
    scanf("%d", &k);
    rep (i, k) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a; --b;
      a = root(a);
      b = root(b);
      int l = lca(a, b);
      int d = (level[first[a]] - level[first[l]]) + (level[first[b]] - level[first[l]]);
      printf("%d\n", d);
    }
  }

  return 0;
}

