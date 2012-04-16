#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define all(c) (c).begin(), (c).end()
#define mp make_pair
#define pb push_back

typedef long long ll;

const double EPS = 1E-9;

int N, B1, B2;
int X[110], Y[110];
double D[110][110];

bool vis[110][110];
double mem[110][110];
pair<int, int> nxt[110][110];

double search(int a, int b) {
  if (a == N - 1 || b == N - 1) return D[a][N - 1] + D[b][N - 1];

  if (vis[a][b]) return mem[a][b];
  vis[a][b] = true;

  int c = max(a, b) + 1;

  double m = 1E30;
  pair<int, int> n = mp(-1, -1);
  if (c != B2) {
    double tm = D[a][c] + search(c, b);
    if (tm < m) { m = tm; n = mp(c, b); }
  }
  if (c != B1) {
    double tm = D[b][c] + search(a, c);
    if (tm < m) { m = tm; n = mp(a, c); }
  }

  vis[a][b] = true;
  mem[a][b] = m;
  nxt[a][b] = n;
  return m;
}


int main() {
  for (int ca = 0; ; ++ca) {
    scanf("%d%d%d", &N, &B1, &B2);
    if (N == 0) return 0;

    rep (i, N) scanf("%d%d", &X[i], &Y[i]);
    rep (i, N) rep (j, N) D[i][j] = hypot(X[i] - X[j], Y[i] - Y[j]);

    memset(vis, 0, sizeof(vis));
    double score = search(0, 0);
    printf("Case %d: %.2f\n", ca + 1, score);

    vector<int> paths[2];
    pair<int, int> c = mp(0, 0);
    paths[0].pb(0);
    paths[1].pb(0);
    while (c.first != N - 1 && c.second != N - 1) {
      pair<int, int> tc = nxt[c.first][c.second];
      if (tc.first != c.first) paths[0].pb(tc.first);
      else paths[1].pb(tc.second);
      c = tc;
    }
    vector<int> p = paths[0];
    reverse(all(paths[1]));
    rep (i, paths[1].size()) p.pb(paths[1][i]);
    int k = p.size();

    if (p[1] != 1) reverse(all(p));

    rep (i, k) printf("%d%c", p[i], i == k - 1 ? '\n' : ' ');

  }
}
