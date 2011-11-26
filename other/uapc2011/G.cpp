#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
#include <cstring>
#include <cassert>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

struct rmq {
  int n;
  vector<int> dat;

  void init(int n_) {
    for (n = 1; n < n_; n *= 2);
    dat.clear();
    dat.resize(2 * n, INT_MAX);
  }

  void update(int k, int a) {
    dat[n + k] = a;
    for (int i = (n + k) / 2; i > 0; i /= 2) {
      dat[i] = min(dat[i * 2], dat[i * 2 + 1]);
    }
  }

  int query(int a, int b) {
    int ret = INT_MAX;
    for (; 0 < a && a + (a & -a) <= b; a += a & -a) {
      int i = (n + a) / (a & -a);
      ret = min(ret, dat[i]);
    }
    for (; a < b; b -= b & -b) {
      int i = (n + b) / (b & -b) - 1;
      ret = min(ret, dat[i]);
    }
    return ret;
  }
};

struct rmq2d {
  static const int S = 30;

  int R, C;
  bool mir;
  vector<rmq> rmq1, rmqS;

  void init(const vector<vector<int> > &data) {
    R = data.size();
    C = data[0].size();
    mir = R > C;
    if (mir) swap(R, C);

    rmq1.resize(R);
    rep (r, R) rmq1[r].init(C);
    rmqS.resize(R / S);
    rep (b, R / S) rmqS[b].init(C);

    rep (r, R) rep (c, C) {
      rmq1[r].update(c, data[mir ? c : r][mir ? r : c]);
    }

    for (int b = 0; (b + 1) * S <= R; ++b) {
      int rlb = b * S, rub = (b + 1) * S;
      rep (c, C) {
        int v = INT_MAX;
        for (int r = rlb; r < rub; ++r) {
          v = min(v, data[mir ? c : r][mir ? r : c]);
        }
        rmqS[b].update(c, v);
      }
    }
  }

  int query(int r1, int r2, int c1, int c2) {  // [r1, r2) x [c1, c2)
    if (mir) {
      swap(r1, c1);
      swap(r2, c2);
    }

    int res = INT_MAX;

    int rub = min(r2, (r1 + S - 1) / S * S);
    for (; r1 < rub; ++r1) {
      res = min(res, rmq1[r1].query(c1, c2));
    }

    int rlb = max(r1, r2 / S * S);
    while (r2 > rlb) {
      --r2;
      res = min(res, rmq1[r2].query(c1, c2));
    }

    for (; r1 < r2; r1 += S) {
      res = min(res, rmqS[r1 / S].query(c1, c2));
    }

    return res;
  }
};






int main() {
  int H, W, Q;
  while (3 == scanf("%d%d%d", &H, &W, &Q) && (H|W|Q)) {
    vector<vector<int> > fld(H, vector<int>(W));
    rep (y, H) rep (x, W) scanf("%d", &fld[y][x]);

    rmq2d r;
    r.init(fld);

    rep (q, Q) {
      int r1, c1, r2, c2;
      scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
      printf("%d\n", r.query(r1, r2 + 1, c1, c2 + 1));
    }
  }
}
