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

p_t cross_l_l(const p_t &p1, const p_t &d1, const p_t &p2, const p_t &d2) {
  double d = det(d1, d2);
  assert(abs(d) > EPS);
  return p1 + d1 * det(p2 - p1, d2) / d;
}


vector<p_t> convex_cut(vector<p_t> &po, p_t p, p_t q) {
  vector<p_t> res;
  for (int i = 0; i < po.size(); i++) {
    p_t a = po[i], b = po[(i+1)%po.size()];
    double pqa = det(q-p, a-p), pqb = det(q-p, b-p);
    if (pqa > -EPS) res.push_back(po[i]);
    if (pqa*pqb < -EPS) res.push_back(cross_l_l(a, b - a, p, q - p));
  }
  return res;
}

double area(const vector<p_t> &po) {
  double s = 0;
  for (int i = 0; i + 1 < (int)po.size(); i++) {
    s += det(po[i] - po[0], po[i + 1] - po[0]) / 2.0;
  }
  return fabs(s);
}

int N, H, F;
int L[510], R[510];

int main() {
  while (3 == scanf("%d%d%d", &N, &H, &F)) {
    rep (i, N) scanf("%d%d", &L[i], &R[i]);

    double s = 0.0;
    rep (i, N) {
      double l1 = R[i] - L[i];
      double l2 = l1 / (F - H) * (F + H);
      s += (l1 + l2) * (2 * H) / 2;
    }
    s *= 2;

    rep (i, N) rep (j, N) {
      vector<p_t> p1;
      p1.pb(p_t(R[i], H));
      p1.pb(p_t(L[i], H));
      p1.pb(p_t(L[i] / double(F - H) * (F + H), -H));
      p1.pb(p_t(R[i] / double(F - H) * (F + H), -H));

      p1 = convex_cut(p1, p_t(R[j], -H), p_t(R[j] / double(F - H) * (F + H), H));
      p1 = convex_cut(p1, p_t(L[j] / double(F - H) * (F + H), H), p_t(L[j], -H));

      s -= area(p1);
      // printf("%d, %d: %f\n", i, j, area(p1));
    }

    printf("%.10f\n", s);
  }

  return 0;
}

