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

#include <complex>
const double EPS = 1e-10;
typedef complex<double> p_t;

double dot(const p_t &p, const p_t &q) { return real(conj(p) * q); }
double det(const p_t &p, const p_t &q) { return imag(conj(p) * q); }

double dist_l_p(const p_t &p, const p_t &a, const p_t &u) {
  return abs(det(p - a, u)) / abs(u);
}

pair<double, double> cross_l_c(p_t a, const p_t &u, const p_t &c, double r) {
  a -= c;
  double b = real(u * conj(a)), d = b * b - norm(u) * (norm(a) - r * r);
  d = max(d, 0.0);
  return make_pair((-b + sqrt(d)) / norm(u), (-b - sqrt(d)) / norm(u));
}

p_t tangent(const p_t &p1, double r1, const p_t &p2, double r2, bool u1, bool u2) {
  double gap = r1 * (u1 ? 1 : -1) - r2 * (u2 ? 1 : -1);
  double a = arg(p2 - p1) + asin(gap / abs(p2 - p1));
  double b1 = a - M_PI / 2.0 * (u1 ? 1 : -1);
  double b2 = a - M_PI / 2.0 * (u2 ? 1 : -1);
  return p2 + polar(r2, b2);
}



int main() {
  p_t P, S;
  double vP, vS, r;
  while (cin >> P.real() >> P.imag() >> vP) {
    cin >> S.real() >> S.imag() >> vS >> r;

    double aP = vP / abs(P);

    double lb = 0.0, ub = 1E30;
    rep (iter, 10000) {
      double t = (lb + ub) / 2;

      p_t p = P * polar(1.0, aP * t);

      if (p == S) {
        ub = t;
        continue;
      }

      double t1 = abs(p - S) / vS;
      // cout << p << S << endl; printf("t = %f, t1 = %f\n", t, t1);

      p_t move = p - S;
      move /= abs(move);
      move *= vS;

      if (dist_l_p(p_t(0, 0), S, move) < r &&
          0  < cross_l_c(S, move, p_t(0, 0), r).first &&
          t1 > cross_l_c(S, move, p_t(0, 0), r).first) {
        // Cross!

        vector<p_t> css, cps;
        css.pb(tangent(S, 0, p_t(0, 0), r, false, false));
        css.pb(tangent(S, 0, p_t(0, 0), r, false, true));

        cps.pb(tangent(p, 0, p_t(0, 0), r, false, false));
        cps.pb(tangent(p, 0, p_t(0, 0), r, false, true));

        double t2 = 1E50;
        rep (i, css.size()) rep (j, cps.size()) {
          p_t cs = css[i], cp = cps[j];
          double a = fabs(arg(cs / cp));
          t2 = min(t2, (abs(cs - S) + r * a + abs(cp - p)) / vS);
        }
        t1 = t2;
      }

      if (t1 < t) ub = t;
      else lb = t;
    }

    printf("%.10f\n", lb);
  }

  return 0;
}

