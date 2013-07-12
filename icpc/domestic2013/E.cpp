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
#include <complex>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

const double EPS = 1e-8;
typedef complex<double> p_t;

namespace std {
  istream &operator>>(istream &is, p_t &p) {
    is >> p.real() >> p.imag();
    return is;
  }
}

double sqr(double x) { return x * x; }

int N;
p_t P[20];
double L[20];
double H;

pair<p_t, p_t> cross_c_c(const p_t &c, double r, const p_t &d, double s) {
  double di = abs(c - d);
  if (di > r + s || di < abs(r - s)) throw "no cross";
  double l = ((r * r - s * s) / di + di) / 2.0, n = sqrt(r * r - l * l);
  p_t e = c + (d - c) * l / di, p = (d - c) * n / di * p_t(0.0, -1.0);
  return make_pair(e + p, e - p);
}

bool test() {
  double r[20];
  rep (i, N) r[i] = sqrt(sqr(L[i]) - sqr(H));

  bool ignore[20] = {};
  vector<p_t> xs;
  rep (i, N) {
    rep (j, N) if (i != j) {
      double d = abs(P[i] - P[j]);
      if (r[j] > r[i] && d < r[j] - r[i]) ignore[j] = true;

      if (d < fabs(r[j] - r[i]) || d >= r[i] + r[j]) continue;
      pair<p_t, p_t> x = cross_c_c(P[i], r[i], P[j], r[j]);
      xs.pb(x.first);
      xs.pb(x.second);
    }
  }

  int n = 0;
  rep (i, N) if (!ignore[i]) ++n;
  if (n <= 1) return true;

  rep (i, xs.size()) {
    p_t x = xs[i];
    rep (i, N) if (abs(x - P[i]) > r[i] + EPS) goto dmp;
    return true;
 dmp:;
  }
  return false;
}

int main() {
  for (;;) {
    cin >> N;
    if (!N) break;
    rep (i, N) cin >> P[i] >> L[i];

    double lb = 0, ub = *min_element(L, L + N);
    rep (iter, 1000) {
      H = (lb + ub) / 2;

      bool t = test();
      if (t) lb = H;
      else ub = H;
    }
    printf("%.10f\n", lb);
  }

  return 0;
}

