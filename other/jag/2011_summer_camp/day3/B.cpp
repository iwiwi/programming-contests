#include <cstdio>
#include <iostream>
using namespace std;

int K;
double L, R;
double P, E, T;

double tbgn, tend;

double search(int k, double b, double e) {
  if (tbgn <= b && e <= tend) return 1.0;
  if (e < tbgn || tend < b) return 0.0;
  if (k == 0) {
    double x = (b + e) / 2.0;
    if (tbgn <= x && x <= tend) return 1.0;
    else return 0.0;
  }

  double m = (b + e) / 2.0;

  double res1 = search(k - 1, b, m);
  double res2 = search(k - 1, m, e);
  double res;

  if (T < m) res = (1.0 - P) * res1 + P * res2;
  else       res = P * res1 + (1.0 - P) * res2;

  return res;
}

int main() {
  while (cin >> K >> R >> L) {
    cin >> P >> E >> T;
    tbgn = T - E;
    tend = T + E;

    printf("%.10f\n", search(K, R, L));
  }
  return 0;
}
