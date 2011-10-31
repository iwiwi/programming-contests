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

int N, M, K;
double KX[1010], KY[1010];
double CR[1010], CX[1010], CY[1010];

int node[1010];
vector<int> adj[1010];

double sqr(double x) { return x * x; }

int where(double x, double y, double reqr = 0.0) {
  double minr = 1E20;
  int minj = -1;
  rep (j, M) {
    double r = CR[j];
    if (r <= reqr || r >= minr) continue;
    
    double rr = sqr(r);
    double dd = sqr(CX[j] - x) + sqr(CY[j] - y);
    if (dd < rr) {
      minr = r;
      minj = j;
    }
  }
  return minj;
}

int dist[1010][1010];

void saiki(int v, int p, int s, int c) {
  dist[s][v] = c;
  rep (i, adj[v].size()) {
    int w = adj[v][i];
    if (w == p) continue;
    saiki(w, v, s, c + 1);
  }
}

int main() {
  while (3 == scanf("%d%d%d", &N, &M, &K)) {
    rep (i, N) scanf("%lf%lf", KX + i, KY + i);
    
    rep (j, M) scanf("%lf%lf%lf", CR + j, CX + j, CY + j);
    CR[M] = 1E10;
    CX[M] = CY[M] = 0;
    ++M;

    rep (i, N) node[i] = where(KX[i], KY[i]);

    rep (j, M) adj[j].clear();
    rep (j, M - 1) {
      int par = where(CX[j], CY[j], CR[j]);
      adj[j].pb(par);
      adj[par].pb(j);
    }

    rep (j, M) saiki(j, -1, j, 0);

    // rep (j, M) {
    //   rep (k, M) printf("%d ", dist[j][k]);
    //   puts("");
    // }
    
    rep (k, K) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      printf("%d\n", dist[node[a]][node[b]]);
    }
  }
  
  return 0;
}

