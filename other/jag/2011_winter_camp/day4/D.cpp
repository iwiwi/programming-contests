#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back

int N, W, H;
int X[40010], Y[40010];
vector<int> hor[100010];
vector<int> ver[100010];

int par[40010];
void init(int n) { 
  rep (i, n) par[i] = i;
}
int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}
void unite(int x, int y) {
  par[root(x)] = root(y);
}

int countit(const vector<int> &ids) {
  vector<int> roots(ids.size());
  rep (i, ids.size()) roots[i] = root(ids[i]);
  sort(roots.begin(), roots.end());
  return unique(roots.begin(), roots.end()) - roots.begin();
}

int main() {
  scanf("%d%d%d", &N, &W, &H);
  rep (i, N) scanf("%d%d", &X[i], &Y[i]);

  rep (i, N) hor[Y[i]].pb(i);
  rep (i, N) ver[X[i]].pb(i);

  // Decompose connected components
  init(N);
  for (int y = 1; y <= H; ++y) {
    for (int i = 0; i + 1 < (int)hor[y].size(); ++i) unite(hor[y][i], hor[y][i + 1]);
  }
  for (int x = 1; x <= W; ++x) {
    for (int i = 0; i + 1 < (int)ver[x].size(); ++i) unite(ver[x][i], ver[x][i + 1]);
  }
  int cc = 0;
  rep (i, N) if (par[i] == i) ++cc;
  int base = N - 1;

  if (cc == 1) {
    printf("%d\n", base);
  }
  else {
    // Wall
    int wall_y1 = cc - countit(hor[1]);
    int wall_yH = cc - countit(hor[H]);
    int wall_x1 = cc - countit(ver[1]);
    int wall_xW = cc - countit(ver[W]);
    printf("%d\n", base + min(min(wall_y1, wall_yH), min(wall_x1, wall_xW)));
  }
  return 0;
}
