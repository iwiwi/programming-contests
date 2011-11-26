#include <cstdio>
#include <cmath>
#include <complex>
#include <map>
using namespace std;
typedef complex<double> p_t;

#define rep(i, n) for (int i = 0; i < (n); ++i)

const double INF = 1E30;
const double EPS = 1E-10;

double dot(p_t p, p_t q) { return real(conj(p) * q); }

int N;
double R, A;
p_t P[30];

double dist[30][30];
bool can[30][30][30];
double pot[30][30][10010];

int main() {
  scanf("%d%lf%lf", &N, &R, &A);
  A = A / 180 * M_PI;
  rep (i, N) scanf("%lf%lf", &P[i].real(), &P[i].imag());
  rep (i, N) rep (j, N) dist[i][j] = abs(P[j] - P[i]);

  double coa = cos(A);
  
  rep (v, N) rep (w, N) rep (x, N) if (v != w && w != x) {
    double co = dot(P[w] - P[v], P[x] - P[w]);
    co /= dist[v][w];
    co /= dist[w][x];
    can[v][w][x] = coa - EPS < co;
  }
  
  const int K = floor(R);

  multimap<double, pair<pair<int, int>, int> > que;
  rep (i, N) rep (j, N) rep (k, K + 1) pot[i][j][k] = INF;
  rep (i, N) if (i != 0) {
    double d = dist[0][i];
    pot[0][i][1] = d;
    que.insert(make_pair(d, make_pair(make_pair(0, i), 1)));
  }

  int ans = 0;
  
  while (!que.empty()) {
    double d = que.begin()->first;
    int v = que.begin()->second.first.first;
    int w = que.begin()->second.first.second;
    int k = que.begin()->second.second;
    que.erase(que.begin());
    if (d > R + EPS) break;
    if (d > pot[v][w][k]) continue;

    ans = max(ans, k);

    rep (x, N) if (can[v][w][x]) {
      double td = d + dist[w][x];
      if (td < pot[w][x][k + 1]) {
        pot[w][x][k + 1] = td;
        que.insert(make_pair(td, make_pair(make_pair(w, x), k + 1)));
      }
    }
  }

  printf("%d\n", ans);
  return 0;
}
