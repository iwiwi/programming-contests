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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

struct segt {
  int n;
  vector<int> dat_sum, dat_max, dat_min;
  vector<bool> lazy_set;
  vector<int> lazy_val;

  void init(int n_) {
    for (n = 1; n < n_; n *= 2);
    dat_sum.clear(); dat_sum.resize(2 * n - 1, 0);
    dat_max.clear(); dat_max.resize(2 * n - 1, 0);
    dat_min.clear(); dat_min.resize(2 * n - 1, 0);
    lazy_set.clear(); lazy_set.resize(2 * n - 1, false);
    lazy_val.clear(); lazy_val.resize(2 * n - 1, false);
  }

  void eval_lazy(int k, int l, int r) {
    if (lazy_set[k]) {
      dat_sum[k] = (r - l) * lazy_val[k];
      dat_max[k] = dat_min[k] = lazy_val[k];
      if (r - l > 1) {
        lazy_val[k * 2 + 1] = lazy_val[k * 2 + 2] = lazy_val[k];
        lazy_set[k * 2 + 1] = lazy_set[k * 2 + 2] = true;
      }
    } else {
      dat_sum[k] += (r - l) * lazy_val[k];
      dat_max[k] += lazy_val[k];
      dat_min[k] += lazy_val[k];
      if (r - l > 1) {
        lazy_val[k * 2 + 1] += lazy_val[k];
        lazy_val[k * 2 + 2] += lazy_val[k];
      }
    }
    lazy_val[k] = 0;
    lazy_set[k] = false;
  }

  void query(int a, int b, int &rmax, int &rmin, int &rsum, int k = 0, int l = 0, int r = 0) {  // [a, b)
    if (k == 0) r = n;
    eval_lazy(k, l, r);
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      rmax = max(rmax, dat_max[k]);
      rmin = min(rmin, dat_min[k]);
      rsum += dat_sum[k];
    } else {
      query(a, b, rmax, rmin, rsum, k * 2 + 1, l, (l + r) / 2);
      query(a, b, rmax, rmin, rsum, k * 2 + 2, (l + r) / 2, r);
    }
  }

  void query_add(int a, int b, int v, int k = 0, int l = 0, int r = 0) {  // [a, b)
    if (k == 0) r = n;
    eval_lazy(k, l, r);
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      lazy_val[k] += v;
      eval_lazy(k, l, r);
    } else {
      int lch = k * 2 + 1, rch = k * 2 + 2;
      query_add(a, b, v, lch, l, (l + r) / 2);
      query_add(a, b, v, rch, (l + r) / 2, r);
      dat_sum[k] = dat_sum[lch] + dat_sum[rch];
      dat_max[k] = max(dat_max[lch], dat_max[rch]);
      dat_min[k] = min(dat_min[lch], dat_min[rch]);
    }
  }

  void query_set(int a, int b, int v, int k = 0, int l = 0, int r = 0) {  // [a, b)
    if (k == 0) r = n;
    eval_lazy(k, l, r);
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      lazy_set[k] = true;
      lazy_val[k] = v;
      eval_lazy(k, l, r);
    }
    else {
      int lch = k * 2 + 1, rch = k * 2 + 2;
      query_set(a, b, v, lch, l, (l + r) / 2);
      query_set(a, b, v, rch, (l + r) / 2, r);
      dat_sum[k] = dat_sum[lch] + dat_sum[rch];
      dat_max[k] = max(dat_max[lch], dat_max[rch]);
      dat_min[k] = min(dat_min[lch], dat_min[rch]);
    }
  }
};



int R, C, M;
segt segs[30];

int main() {
  while (3 == scanf("%d%d%d", &R, &C, &M)) {
    rep (y, R) segs[y].init(C);

    rep (i, M) {
      int q, x1, y1, x2, y2, v;
      scanf("%d%d%d%d%d", &q, &y1, &x1, &y2, &x2);
      --x1; --y1;

      if (q == 1) {
        scanf("%d", &v);
        for (int y = y1; y < y2; ++y) segs[y].query_add(x1, x2, v);
      } else if (q == 2) {
        scanf("%d", &v);
        for (int y = y1; y < y2; ++y) segs[y].query_set(x1, x2, v);
      } else {
        int rmin = INT_MAX, rmax = INT_MIN, rsum = 0;
        for (int y = y1; y < y2; ++y) segs[y].query(x1, x2, rmax, rmin, rsum);
        printf("%d %d %d\n", rsum, rmin, rmax);
      }
    }

    rep (y, R) segs[y].init(1);
  }

  return 0;
}

