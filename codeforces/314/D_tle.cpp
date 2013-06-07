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
#define X first
#define Y second

typedef long long ll;

const int MAX_N = 100000;

int n, di[4 * MAX_N], ma[4 * MAX_N];

void init(int n_) {
  for (n = 1; n < n_; n *= 2);
  fill(di, di + 2 * n - 1, 0);
  fill(ma, ma + 2 * n - 1, 0);
}

int query(int a, int b, int v, int k = 0, int l = 0, int r = 0) { // [a, b) += v
  if (k == 0) r = n;
  if (r <= a || b <= l) {
    return ma[k];
  } else if (a <= l && r <= b) {
    di[k] += v;
    return ma[k] += v;
  } else {
    int vl = query(a, b, v, k * 2 + 1, l, (l + r) / 2);
    int vr = query(a, b, v, k * 2 + 2, (l + r) / 2, r);
    return ma[k] = di[k] + max(vl, vr);
  }
}



int N;
pair<ll, ll> P[1000010];

vector<int> ys;

inline int getyi(int y) {
  return lower_bound(all(ys), y) - ys.begin();
}

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) {
      int x, y;
      scanf("%d%d", &x, &y);
      P[i] = mp(ll(x + y) * 2, ll(x - y) * 2);
    }
    sort(P, P + N);

    ll lb = -1, ub = 1E10;
    while (ub - lb > 1) {
      ll w = (lb + ub) / 2;

      ys.clear();
      rep (i, N) {
        ys.pb(P[i].Y - w);
        ys.pb(P[i].Y + w + 1);
      }
      sort(all(ys));
      ys.erase(unique(all(ys)), ys.end());

      init(ys.size());
      rep (i, N) query(getyi(P[i].Y - w), getyi(P[i].Y + w + 1), +1);

      int r = 0;  // [l, r)
      rep (l, N) {
        while (r < N && P[r].X <= P[l].X + 2 * w) {
          query(getyi(P[r].Y - w), getyi(P[r].Y + w + 1), -1);
          ++r;
        }
        if (ma[0] + (r - l) == N) goto ok;
        query(getyi(P[l].Y - w), getyi(P[l].Y + w + 1), +1);
      }

      lb = w;
      continue;
   ok:
      ub = w;
    }

    printf("%.10f\n", ub / 2.0);
  }

  return 0;
}
