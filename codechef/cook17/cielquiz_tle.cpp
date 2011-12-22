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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

#define F first
#define S second



#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>

struct __bench__ {
  double start;
  char msg[100];
  __bench__(const char* format, ...)
  __attribute__((format(printf, 2, 3)))
  {
    va_list args;
    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    start = sec();
  }
  ~__bench__() {
    // fprintf(stderr, "%s: %.6f sec\n", msg, sec() - start);
  }
  double sec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
  }
  operator bool() { return false; }
};

#define benchmark(...) if(__bench__ __b__ = __bench__(__VA_ARGS__));else




typedef long long ll;

typedef pair<double, double> pdd;
typedef pair<pair<double, double>, ll> pddl;


void init(int n, double *p, pdd *a) {
  a[0] = mp(0.0, 1.0);
  for (int b = 1; b < 1 << n; ++b) {
    rep (i, n) if (b & (1 << i)) {
      int tb = b - (1 << i);
      a[b] = mp(a[tb].first  * p[i] + a[tb].second * (1.0 - p[i]),
                a[tb].second * p[i]);
      break;
    }
  }
}

void enumerate(int n, int k, double *p, pdd *a, vector<pddl> &res) {
  vector<pddl> tmp;
  tmp.reserve(1 << n);

  benchmark("enumerate") {
  for (int m = (1 << k) - 1; m < (1 << n); ) {
    // double p0 = 0.0, p1 = 1.0;
    // rep (i, n) if (m & (1 << i)) {
    //   p0 = p0 * p[i] + p1 * (1.0 - p[i]);
    //   p1 = p1 * p[i];
    // }
    // tmp.pb(mp(mp(p0, p1), m));

    tmp.pb(mp(a[m], m));

    if (k == 0) break;
    int x = m & -m;
    int y = m + x;
    m = ((m & ~y) / x >> 1) | y;
  }
  }

  benchmark("sort") {
    sort(all(tmp));
  }

  res.clear();
  res.reserve(1 << n);

  benchmark("hull") {
  rep (i, tmp.size()) {
    while (!res.empty() && res.back().F.S <= tmp[i].F.S) res.pop_back();

    while (res.size() >= 2) {
      pddl &a = res[res.size() - 2], &b = res[res.size() - 1], &c = tmp[i];
      double y = (a.F.S * (c.F.F - b.F.F) + c.F.S * (b.F.F - a.F.F));
      if (y > b.F.S * (c.F.F - a.F.F)) {
        // printf("%lf %lf, %lf %lf, %lf %lf : %lf\n", a.F.F, a.F.S, b.F.F, b.F.S, c.F.F, c.F.S, y);
        // puts("YES");
        res.pop_back();
      }
      else break;
    }

    res.pb(tmp[i]);
  }
  }
}

inline double prb(const pddl &a, const pddl &b) {
  return a.F.F * b.F.S + a.F.S * b.F.F;
}


pdd la[1 << 18], ra[1 << 18];

int main() {
  int T;
  scanf("%d", &T);
  rep (ca, T) {
    int N, K;
    double P[40];

    scanf("%d%d", &N, &K);
    rep (i, N) {
      scanf("%lf", &P[i]);
      P[i] /= 100;
    }

    int L = N / 2;
    int R = N - L;

    benchmark("init") {
      init(L, P, la);
      init(R, P + L, ra);
    }

    double best_p = -1.0;
    ll best_b = 0;
    for (int lk = 0; lk <= K; ++lk) {
      int rk = K - lk;
      if (lk > L || rk > R) continue;

      vector<pddl> lv, rv;
      enumerate(L, lk, P, la, lv);
      enumerate(R, rk, P + L, ra, rv);
       // printf("lk = %d\n", lk);
       // rep (i, lv.size()) printf("(%lf, %lf), ", lv[i].F.F, lv[i].F.S); puts("");
       // rep (i, rv.size()) printf("(%lf, %lf), ", rv[i].F.F, rv[i].F.S); puts("");

      benchmark("sweep") {
      int ri = rv.size() - 1;
      rep (li, lv.size()) {
        double p = prb(lv[li], rv[ri]), q;
        while (ri > 0 && (q = prb(lv[li], rv[ri - 1])) > p) {
          --ri;
          p = q;
        }

        // printf(" (%lf, %lf) vs (%lf, %lf), %lf\n", lv[li].F.F, lv[li].F.S, rv[ri].F.F, rv[ri].F.S, p);

        if (best_p < p) {
          // printf("  %e -> %e (%e)\n", best_p, p, p - best_p);
          best_p = p;
          best_b = lv[li].S | (rv[ri].S << L);
        }
      }
      }
    }

    bool f = true;
    rep (i, N) if ((best_b >> i) & 1) {
      if (f) f = false;
      else printf(" ");
      printf("%d", i + 1);
    }
    puts("");
  }

  return 0;
}

