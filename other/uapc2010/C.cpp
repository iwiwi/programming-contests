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

namespace std {
  istream &operator>>(istream &is, p_t &p) {
    is >> p.real() >> p.imag();
    return is;
  }
}
double dot(const p_t &p, const p_t &q) { return real(conj(p) * q); }
double det(const p_t &p, const p_t &q) { return imag(conj(p) * q); }

pair<double, double> cross_l_c(p_t a, const p_t &u, const p_t &c, double r) {
  a -= c;
  double b = real(u * conj(a)), d = b * b - norm(u) * (norm(a) - r * r);
  d = max(d, 0.0);
  return make_pair((-b + sqrt(d)) / norm(u), (-b - sqrt(d)) / norm(u));
}

double dist_l_p(const p_t &p, const p_t &a, const p_t &u) {
  return abs(det(p - a, u)) / abs(u);
}




int main() {
  for (;;) {
    double D;
    cin >> D;
    if (D == 0.0) return 0;
    
    p_t P, V;
    cin >> P >> V;

    p_t O(0.0, 0.0);
    for (;;) {
      if (fabs(det(O - P, V)) < EPS && dot(O - P, V) > EPS) {
        // goal!!
        double d = abs(O - P);
        if (d > D) goto imp;
        printf("%.10f\n", d);
        break;
      }

      pair<double, double> ss = cross_l_c(P, V, O, 1.0);
      double s = max(ss.first, ss.second);

      p_t x = P + s * V;
      if (abs(x - P) > D) goto imp;
      
      p_t r = x * polar(1.0, M_PI / 2.0);
      double d = dist_l_p(P, x, r);
      //printf("d=%f\n", d);
      P = P + x / abs(x) * (d * 2);

      double a = arg(r / V);
      V *= polar(1.0, a * 2.0);

      //cout << P << V << endl;
    }
    continue;
    
  imp:
    puts("impossible");
  }
  
  
  return 0;
}

