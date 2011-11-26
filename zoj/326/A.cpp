#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <set>
#include <iostream>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define mp make_pair

const int INF = 987654321;

double nijo(double x) { return x * x; }

double X, R0, R1;

double F(double x) {
  double r0, r1;

  if (fabs(x) >= R0) r0 = 0;
  else r0 = sqrt(nijo(R0) - nijo(x));

  if (fabs(x - X) >= R1) r1 = 0;
  else r1 = sqrt(nijo(R1) - nijo(x - X));

  double r = max(r0, r1);
  return r * r * M_PI;
}

double simpson(double (*f)(double), double x0, double x1, int n) {
  double dx = x1 - x0, s = -f(x0);
  for (int i = 0; i < n; i += 2) {
    s += 2.0 * f(x0 + dx * i / n);
    s += 4.0 * f(x0 + dx * (i + 1) / n);
  }
  s += f(x1);
  return s / 3 * dx / n;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    double x1, y1, z1, r1, x2, y2, z2, r2;
    cin >> x1 >> y1 >> z1 >> r1 >> x2 >> y2 >> z2 >> r2;

    X = sqrt(nijo(x1 - x2) + nijo(y1 - y2) + nijo(z1 - z2));
    R0 = r1;
    R1 = r2;

    printf("%.2f\n", simpson(F, -100, 500, 1000000));
  }
}
