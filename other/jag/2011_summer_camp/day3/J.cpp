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

const int MAX_V = 110;
const double EPS = 1E-10;

int N;
vector<int> adj[MAX_V], rev[MAX_V];
bool vis[MAX_V];
int ord[MAX_V], num, id[MAX_V];

void dfs1(int v) {
  if (vis[v]) return;
  vis[v] = true;
  rep (i, adj[v].size()) dfs1(adj[v][i]);
  ord[num++] = v;
}

void dfs2(int v) {
  if (vis[v]) return;
  vis[v] = true; id[v] = num;
  rep (i, rev[v].size()) dfs2(rev[v][i]);
}

void scc() {
  memset(vis, 0, sizeof(vis)); num = 0;
  rep (i, N) dfs1(i);
  memset(vis, 0, sizeof(vis)); num = 0;
  for (int i = N - 1; i >= 0; --i) if (!vis[ord[i]]) dfs2(ord[i]), num++;
}




int saiki(int v) {
  if (vis[v]) return 0;
  vis[v] = true;
  int res = 1;
  rep (i, adj[v].size()) res += saiki(adj[v][i]);
  return res;
}

double minimum_spanning_arborescence(
    int n, int r, vector<int> *ra, vector<double> *rw)
{
  double c, res = 0;
  rep (i, n) {
    adj[i].clear();
    rev[i].clear();
  }
  rep (i, n) {
    if (i == r) continue;
    res += (c = *min_element(rw[i].begin(), rw[i].end()));
    rep (j, ra[i].size()) {
      if ((rw[i][j] -= c) < EPS) {
        adj[ra[i][j]].pb(i);
        rev[i].pb(ra[i][j]);
      }
    }
  }
  memset(vis, 0, sizeof(vis));
  if (saiki(r) == n) return res;

  N = n;
  scc();

  int m = num;
  vector<int> *nra = new vector<int>[m];
  vector<double> *nrw = new vector<double>[m];

  rep (i, n) rep (j, ra[i].size()) {
    if (id[i] == id[ra[i][j]]) continue;
    nra[id[i]].pb(id[ra[i][j]]);
    nrw[id[i]].pb(rw[i][j]);
  }
  return res += minimum_spanning_arborescence(m, id[r], nra, nrw);
}



double dot(const vector<double> &v, const vector<double> &w) {
  double r = 0.0;
  rep (i, v.size()) r += v[i] * w[i];
  return r;
}

double abs2jo(const vector<double> &v) {
  return dot(v, v);
}

double nijo(double x) { return x * x; }

double diff(const vector<double> &from, const vector<double> &to) {
  // printf("%f\n", abs2jo(from));
  // printf("%f, %f\n", dot(from, to), nijo(dot(from, to)));
  // printf("%f\n", abs2jo(to));
  return abs2jo(to) - nijo(dot(from, to)) / abs2jo(from);
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    vector<double> v[110];
    // printf("n=%d, m=%d\n", n, m);
    rep (i, m) {
      v[i].resize(n);
      rep (j, n) cin >> v[i][j];
    }

    // rep (i, m) printf("%f\n", abs2jo(v[i]));
    // rep (i, m) rep (j, m) if (i != j) {
    //   printf("%d -> %d: %f\n", i, j, diff(v[i], v[j]));
    // }


    // !!!!!!!!!REVERSE!!!!!!!!!!!
    vector<int> ra[110];
    vector<double> rw[110];

    // Start
    rep (i, m) {
      ra[i].pb(m);
      rw[i].pb(abs2jo(v[i]));
    }
    // Diff
    rep (i, m) rep (j, m) {
      // i -> j
      if (i == j) continue;
      ra[j].pb(i);
      rw[j].pb(diff(v[i], v[j]));
    }

    printf("%.10f\n", minimum_spanning_arborescence(m + 1, m, ra, rw));
  }

  return 0;
}
