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

struct seg {
  double l, r, m, a;
  explicit seg(double l = 0, double r = 0, double m = 0, double a = 0) : l(l), r(r), m(m), a(a) {}
};

const int MAX_N = 150000;

int n;
seg dat[4 * MAX_N];

seg merge(seg &l, seg &r) {
  return (seg)
  {   max(l.l, l.a + r.l),
        max(r.r, l.r + r.a),
        max(max(l.m, r.m), l.r + r.l),
        l.a + r.a};
}

void init(int n_) {
  for (n = 1; n < n_; n *= 2);
}

void update(int k, double a) {
  k += n - 1;
  dat[k] = seg(a, a, a, a);
  while (k > 0) {
    k = (k - 1) / 2;
    dat[k] = merge(dat[k * 2 + 1], dat[k * 2 + 2]);

  }
}

seg query(int a, int b, int k = 0, int l = 0, int r = 0) { // [a, b)
  if (k == 0) r = n;
  if (r <= a || b <= l) return seg(0, 0, -1E30, 0);
  if (a <= l && r <= b) return dat[k];
  else {
    seg vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
    seg vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
    seg s = merge(vl, vr);
    assert(s.a <= s.m);

    // printf("%d = [%d, %d): %lf %lf %lf %lf\n", k, max(a, l), min(b, r), s.l, s.r, s.m, s.a);

    return s;
  }
}


int X[1000010];
int P[1000010];

int main() {
  int N, M, C;
  while (3 == scanf("%d%d%d", &N, &M, &C)) {
    rep (i, N) scanf("%d", &X[i]);
    rep (i, N - 1) scanf("%d", &P[i]);

    int S = N - 1;
    init(S);
    rep (i, S) {
      // printf("%d: %lf\n", i,  (X[i + 1] - X[i]) / 2.0 - C * P[i] / 100.0);
      update(i, (X[i + 1] - X[i]) / 2.0 - C * P[i] / 100.0);
    }

    // rep (i, n * 2 - 1) const seg &s = dat[i]; printf("! %d = %lf %lf %lf %lf\n", i, s.l, s.r, s.m, s.a);

    double res = 0.0;
    rep (i, M) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;

      // if (a == 0 && b == 4); else continue;

      seg s = query(a, b);
      res += max(0.0, s.m);
      printf("[%d, %d): %lf %lf -> %lf\n", a, b, s.a, s.m, -s.a + max(0.0, s.m));
    }
    printf("%.10f\n", res);
  }

  return 0;
}

