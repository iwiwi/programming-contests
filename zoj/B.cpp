#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <deque>
#include <cmath>
#include <cstdlib>
#include <cassert>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define mp make_pair

typedef long long ll;

const double gr = 2 / (3 + sqrt(5));
const int iter_n = 500;

double golden(double l, double r, double f(double)) {
  double ml = l + gr * (r - l), mr = r - gr * (r - l);
  double fml = f(ml), fmr = f(mr);
  for (int iter = 0; iter < iter_n; ++iter) {
    if (fml > fmr) {
      l = ml;
      ml = mr;
      mr = r - gr * (r - l);
      fml = fmr;
      fmr = f(mr);
    } else {
      r = mr;
      mr = ml;
      ml = l + gr * (r - l);
      fmr = fml;
      fml = f(ml);
    }
  }
  return fml;
}

double global_r;
double global_R;

double search_H(double h) {
  double r = global_r;
  double R = global_R;
  double H = ((1/M_PI) - h * (R*R + r*R + r*r) / 3) / (R*R);

  //double area = M_PI * (r*r + 2*R*H + (R*R-r*r) * sqrt(1 + h*h / (R-r)*(R-r)));
  double area = M_PI * (r*r + 2*R*H + (R+r) * sqrt((R-r)*(R-r) + h*h));
  return area;
}

double search_h(double R) {
  double r = global_r;
  double h_ub = (1/M_PI) / ((R*R + r*R + r*r) / 3);
    
  global_R = R;
  return golden(0.0, h_ub, search_H);
}

double search_R(double r) {
  global_r = r;
  return golden(r, 100, search_h);
}

double search_r() {
  return golden(0.0, 100, search_R);
}

int main() {
  printf("%.20f\n", search_r());
  
  return 0;
}
