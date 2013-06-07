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

int N;
pair<ll, ll> P[100010];

ll mimal[100010], mamil[100010];
ll mimar[100010], mamir[100010];

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

      mimal[0] = mimar[N] = INT_MAX;
      mamil[0] = mamir[N] = INT_MIN;
      rep (i, N) {
        mimal[i + 1] = min(mimal[i], P[i].Y + w + 1);
        mamil[i + 1] = max(mamil[i], P[i].Y - w);
      }
      for (int i = N - 1; i >= 0; --i) {
        mimar[i] = min(mimar[i + 1], P[i].Y + w + 1);
        mamir[i] = max(mamir[i + 1], P[i].Y - w);
      }

      int r = 0;  // [l, r)
      rep (l, N) {
        while (r < N && P[r].X <= P[l].X + 2 * w) ++r;
        if (max(mamil[l], mamir[r]) <= min(mimal[l], mimar[r])) goto ok;
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

