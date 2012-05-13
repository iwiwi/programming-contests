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
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int N, A, B;
char fld[50][50];

const int MAX_V = 1010;
struct e_t { int to, init, cap, cst, rev; };
int V;

vector<e_t> adj[MAX_V];
double h[MAX_V];
int ex[MAX_V], iter[MAX_V];;
bool visit[MAX_V];

void add_edge(int i, int j, int cap, int cst) {
  adj[i].push_back((e_t){j, cap, cap, +cst, adj[j].size()});
  adj[j].push_back((e_t){i,   0,   0, -cst, adj[i].size() - 1});
}

void dfs(int v) {
  visit[v] = true;
  rep (i, adj[v].size()) {
    e_t &e = adj[v][i];
    if (e.cap > 0 && !visit[e.to] && e.cst + h[v] - h[e.to] < 0) dfs(e.to);
  }
}

int dfs(int v, int f) {
  if (ex[v] < 0) {
    int d = min(f, -ex[v]);
    ex[v] += d;
    return d;
  }
  for (; iter[v] < (int)adj[v].size(); ++iter[v]) {
    e_t &e = adj[v][iter[v]];
    if (e.cap > 0 && e.cst + h[v] - h[e.to] < 0) {
      int d = dfs(e.to, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        adj[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int min_cost_circulation() {
  double eps = 0;
  rep (v, V) rep (i, adj[v].size()) if (adj[v][i].cap > 0) eps = max(eps, -(double)adj[v][i].cst);
  while (eps * (V + 1) > 1) {
    eps /= 4;
    rep (v, V) rep (i, adj[v].size()) {
      e_t &e = adj[v][i];
      if (e.cap > 0 && e.cst + h[v] - h[e.to] < 0) {
        ex[e.to] += e.cap;
        ex[v] -= e.cap;
        adj[e.to][e.rev].cap += e.cap;
        e.cap = 0;
      }
    }
    for (;;) {
      rep (v, V) visit[v] = false;
      rep (v, V) if (ex[v] > 0) dfs(v);
      rep (v, V) if (visit[v]) h[v] -= eps;
      rep (v, V) iter[v] = 0;
      bool ok = true;
      rep (v, V) {
        for (int f; ex[v] > 0 && (f = dfs(v, ex[v])) > 0; ) ex[v] -= f;
        if (ex[v] > 0) ok = false;
      }
      if (ok) break;
    }
  }
  int res = 0;
  rep (v, V) rep (i, adj[v].size()) {
    e_t &e = adj[v][i];
    if (e.init > e.cap) res += e.cst * (e.init - e.cap);
  }
  return res;
}


const int L = 10000;

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d%d", &N, &A, &B);
    if (N == 0 && A == 0 && B == 0) return 0;
    rep (i, N) scanf("%s", fld[i]);

    int ans = -1;
    for (int a = 0; a <= N; ++a) {
      V = N * 2;
      rep (v, V) adj[v].clear();

      int c = 0;
      rep (i, N) rep (j, N) {
        switch (fld[i][j]) {
          case 'C':
            add_edge(i, N + j, 1, -L);
            ++c;
            break;
          case '.':
            add_edge(i, N + j, 1, 0);
            break;
          case '/':
            break;
        }
      }

      rep (i, N) add_edge(N + i, i, a, -1);

      int f = -min_cost_circulation();
      if (f < c * L) continue;  // 'C'
      int k = f - c * L;
      // printf("%d %d\n", k, tot);
      if (k * A >= a * B) ans = max(ans, k - c);
    }

    printf("Case %d: ", ca);
    if (ans == -1) puts("impossible");
    else printf("%d\n", ans);
  }

  return 0;
}

