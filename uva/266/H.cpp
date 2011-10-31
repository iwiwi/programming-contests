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

map<vector<int>, double> mem;

double saiki(const vector<int> &v) {
  iter(mem) ite = mem.find(v);
  if (ite != mem.end()) return ite->second;

  int w = v.size();
  int h = *max_element(all(v));
  if (h == 0) return 0.0;

  double res = 0.0;
  for (int y = 1; y <= h; ++y) {
    rep (d, 2) {
      double win = 0.0;
      for (int p = 1; p <= 3; ++p) {
        vector<int> tv = v;
        if (d) reverse(all(tv));
        int r = p;
        rep (x, w) {
          if (tv[x] >= y && r > 0) {
            --tv[x];
            --r;
          }
        }
        win += (1.0 - saiki(tv)) / 3.0;
      }
      res = max(res, win);
    }
  }

  return mem[v] = res;
}

int main() {
  for (;;) {
    int N;
    scanf("%d", &N);
    if (!N) return 0;

    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);

    printf("%.6f\n", saiki(A));
  }

  return 0;
}

