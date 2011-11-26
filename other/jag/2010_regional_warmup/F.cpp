#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <complex>
#include <iostream>

using namespace std;

const int INF = 987654321;

typedef long long ll;
typedef complex<double> p_t;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back
#define mp make_pair

int main() {
  freopen("F.txt", "r", stdin);

  for (;;) {
    int N;
    double D;
    scanf("%d%lf", &N, &D);
    if (N == 0 && D == 0) return 0;

    p_t lp(-D, 0.0);
    p_t rp(D, 0.0);
    
    rep (i, N) {
      double ls, rs, t;
      scanf("%lf%lf%lf", &ls, &rs, &t);
      if (ls == 0 && rs == 0) continue;
      
      ls = ls / 180.0 * M_PI;
      rs = rs / 180.0 * M_PI;
      double ld = ls * t;
      double rd = rs * t;

      // printf(" ld = %f\n", ld);
      
      if (ls == rs) {
        p_t v = rp - lp;
        v *= polar(1.0, M_PI / 2.0);
        v *= ld / abs(v);
        // cout << " v = " << v << endl;
        lp += v;
        rp += v;
        continue;
      }

      double a = (rs + ls) / (rs - ls) * D;
      double th;
      if (ls == 0) th = rd / (a + D);
      else th = ld / (a - D);
      // printf(" a = %f\n", a);
      // printf(" th = %f\n", th);

      p_t v = lp - rp;
      v /= abs(v);
      p_t o = (lp + rp) / 2.0 + v * a;

      lp = o + (lp - o) * polar(1.0, th);
      rp = o + (rp - o) * polar(1.0, th);

//       printf(" %f\n", abs(lp - rp));
//       cout << " " << lp << " " << rp << endl;
    }

    p_t cp = (lp + rp) / 2.0;
    printf("%.10f\n", cp.real());
    printf("%.10f\n", cp.imag());
  }
}
