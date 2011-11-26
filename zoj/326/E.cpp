#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>
#include <cstdlib>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)

typedef complex<double> c_t;

char buf[1000010];

vector<c_t> readline() {
  if (gets(buf) == NULL) exit(0);
  if (strlen(buf) == 0) exit(0);

  vector<c_t> res;

  stringstream ss(buf);
  for (string s; ss >> s; ) {
    c_t c;
    sscanf(s.c_str(), "(%lf,%lf)", &c.real(), &c.imag());
    res.push_back(c);
  }

  return res;
}

int main() {
  for (;;) {
    vector<c_t> X = readline();
    vector<c_t> Y = readline();

    gets(buf);
    double P = atof(buf);

    double s = 0.0;
    rep (i, X.size()) s += pow(abs(X[i] - Y[i]), P);
    s = pow(s, 1 / P);

    printf("%.10f\n", s);
  }
}
