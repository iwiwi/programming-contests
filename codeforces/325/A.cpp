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


int main() {
  int N;
  while (cin >> N) {
    int x1[10], y1[10], x2[10], y2[10];
    rep (i, N) cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];

    map<int, int> xs, ys;
    rep (i, N) xs[x1[i]] = xs[x2[i]] = ys[y1[i]] = ys[y2[i]] = 0;
    int X = 0, Y = 0;
    tr (xs, ite) ite->second = X++;
    tr (ys, ite) ite->second = Y++;

    bool fld[110][110] = {};
    rep (i, N) {
      for (int y = ys[y1[i]]; y < ys[y2[i]]; ++y) {
        for (int x = xs[x1[i]]; x < xs[x2[i]]; ++x) {
          fld[y][x] = true;
        }
      }
    }

    if (*max_element(x2, x2 + N) - *min_element(x1, x1 + N) !=
        *max_element(y2, y2 + N) - *min_element(y1, y1 + N)) {
      goto dmp;
    }

    rep (y, Y - 1) rep (x, X - 1) if (!fld[y][x]) goto dmp;
    puts("YES");
    continue;
 dmp:
    puts("NO");
  }

  return 0;
}

