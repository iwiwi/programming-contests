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
#define eb(e) emplace_back(e)
#define mp(a, b) make_pair(a, b)

uint32_t xor128_x = 123456789;
uint32_t xor128_y = 362436069;
uint32_t xor128_z = 521288629;
uint32_t xor128_w = 88675123;

void xor128_srand(uint32_t w) {
  xor128_w = w;
}

uint32_t xor128() {
  uint32_t t = xor128_x ^ (xor128_x << 11);
  xor128_x = xor128_y; xor128_y = xor128_z; xor128_z = xor128_w;
  return xor128_w = (xor128_w ^ (xor128_w >> 19)) ^ (t ^ (t >> 8));
}

double gen() {
  return xor128() / (double)numeric_limits<uint32_t>::max();
}

double white() {
  return sqrt(-log(gen())) * sin(2 * M_PI * gen());
}

double black() {
  return gen() + gen() + gen() + gen() + gen() + gen() - 3;
}

double score(vector<double> a) {
  double s = 0.0;
  rep (i, a.size()) s += fabs(a[i] * a[i] * a[i] * a[i] * a[i] * a[i] * a[i] * a[i]);
  return s;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    const int N = 2000;
    rep (k, 100) {
      {
        vector<double> w(N);
        rep (i, N) w[i] = white();
        printf("%.3f\t", score(w));
      }
      {
        vector<double> b(N);
        rep (i, N) b[i] = black();
        printf("%.3f\t", score(b));
      }
      puts("");
    }
    return 0;
  }

  int T;
  scanf("%d", &T);
  vector<pair<double, int> > s;
  rep (t, T) {
    int N;
    scanf("%d", &N);
    vector<double> X(N);
    rep (i, N) scanf("%lf", &X[i]);
    s.emplace_back(score(X), t);
  }

  sort(all(s));
  vector<string> ans(T);
  rep (t, T) {
    ans[s[t].second] = (t < T / 2 ? "Black" : "White");
  }

  rep (t, T) {
    cout << ans[t] << endl;
  }

  return 0;
}
