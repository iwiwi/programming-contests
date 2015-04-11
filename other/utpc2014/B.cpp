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

typedef long long ll;

const double EPS = 1e-10;
typedef complex<double> p_t;

double dot(const p_t &p, const p_t &q) { return real(conj(p) * q); }
double det(const p_t &p, const p_t &q) { return imag(conj(p) * q); }

p_t cross_l_l(const p_t &p1, const p_t &d1, const p_t &p2, const p_t &d2) {
  double d = det(d1, d2);
  assert(abs(d) > EPS);
  return p1 + d1 * det(p2 - p1, d2) / d;
}


inline ll absll(ll x) {
  return x >= 0 ? x : -x;
}

inline ll div_at_most(ll a, ll b) {  // x <= a/b
  return (a < 0) ^ (b < 0) ? -(absll(a) + absll(b) - 1) / absll(b) : absll(a) / absll(b);
}

void check(ll x) {
  assert(absll(x) <= 10000);
}

int signum(int x) {
  return x < 0 ? -1 : 1;
}

int main() {
  int x1, x2, y1, y2;
  while (4 == scanf("%d.%d %d.%d", &x1, &x2, &y1, &y2)) {
    ll X1000 = signum(x1) * (absll(x1) * 1000 + x2);
    ll Y1000 = signum(y1) * (absll(y1) * 1000 + y2);
    fprintf(stderr, "%lld %lld\n", X1000, Y1000);

    ll X = div_at_most(X1000, 1000);
    ll Y = div_at_most(Y1000, 1000);
    ll xxx = X1000 - X * 1000;
    ll yyy = Y1000 - Y * 1000;
    assert(0 <= xxx && xxx < 1000);
    assert(0 <= yyy && yyy < 1000);
    // printf("%lld+0.%03lld %lld+0.%03lld\n", X, xxx, Y, yyy);

    ll x11 = X - 1, y11 = Y, x12 = (X - 1) + (1000 + xxx), y12 = Y + yyy;
    ll x21 = X, y21 = Y - 1, x22 = X + xxx, y22 = (Y - 1) + (1000 + yyy);
    check(x11); check(y11); check(x12); check(y12);
    check(x21); check(y21); check(x22); check(y22);

    printf("%lld %lld %lld %lld\n", x11, y11, x12, y12);
    printf("%lld %lld %lld %lld\n", x21, y21, x22, y22);
  }
}
