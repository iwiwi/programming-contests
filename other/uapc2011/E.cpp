#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

const double EPS = 1E-9;

#include <complex>
typedef complex<double> p_t;

double det(const p_t &p, const p_t &q) { return imag(conj(p) * q); }

pair<p_t, p_t> cross_c_c(const p_t &c, double r, const p_t &d, double s) {
  double di = abs(c - d);
  double l = ((r * r - s * s) / di + di) / 2.0, n = sqrt(r * r - l * l);
  p_t e = c + (d - c) * l / di, p = (d - c) * n / di * p_t(0.0, -1.0);
  return make_pair(e + p, e - p);
}



int N, R, Q;

int main() {
  while (cin >> N >> R >> Q && (N|R|Q)) {
    vector<p_t> P(N);
    rep (i, N) scanf("%lf%lf", &P[i].real(), &P[i].imag());

    p_t c;
    rep (i, N) if (fabs(abs(P[i]) - R) < EPS) c = P[i];
    // cout << c << endl;

    rep (q, Q) {
      // (angle, (-dist, point))
      double ba = 1E30;
      double br = -1E30;
      p_t bc;

      rep (i, N) {
        double td = abs(P[i] - c);
        if (td < EPS) continue;  // center

        // cout << td << endl;

        pair<p_t, p_t> cps_ = cross_c_c(p_t(0.0, 0.0), R, c, td);
        vector<p_t> cps;
        cps.pb(cps_.first);
        cps.pb(cps_.second);

        rep (j, cps.size()) {
          p_t tc = cps[j];

          if (det(c, tc) > 0.0) continue;

          double ta = arg((tc - c) / (P[i] - c));
          if (ta < 0) ta += 2 * M_PI;

          double tr = arg(c / tc);

          // cout << P[j] << " -> " << cps[j] << endl;
          // cout << ta << endl;

          if (ta < ba - EPS || (ta < ba + EPS && tr > br)) {
            ba = ta;
            br = tr;
            bc = tc;
          }
        }
      }

      // printf("rot: %f\n", ba);
      // printf("rot2: %f\n", br);

      rep (i, N) P[i] = c + (P[i] - c) * polar(1.0, ba);
      c = bc;
      printf("%.10f %.10f\n", bc.real(), bc.imag());

      // return 0;
    }
  }
}
