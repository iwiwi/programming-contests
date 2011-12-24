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

typedef long double ld;

int N, M;


int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    vector<pair<int, int> > evt;
    rep (i, N) {
      int a, h, l, r;
      scanf("%d%d%d%d", &a, &h, &l, &r);
      evt.pb(mp(a - h, l)); evt.pb(mp(a, -l));
      evt.pb(mp(a + 1, r)); evt.pb(mp(a + h + 1, -r));
    }
    sort(all(evt));

    vector<pair<int, int> > mush;
    rep (i, M) {
      int b, z;
      scanf("%d%d", &b, &z);
      mush.pb(mp(b, z));
    }
    sort(all(mush));

    ld ans = 0.0;

    int j = 0;
    double r = 0.0;
    int np1 = 0;
    rep (i, mush.size()) {
      int x = mush[i].first;
      int z = mush[i].second;

      while (j < (int)evt.size() && evt[j].first <= x) {
        int p = evt[j].second;
        if (p > 0) {
          if (p == 100) ++np1;
          else r += log(1.0 - p / 100.0);
          // printf("> %d\n", p);
        }
        if (p < 0) {
          p *= -1;
          if (p == 100) --np1;
          else r -= log(1.0 - p / 100.0);
          // printf("< %d\n", p);
        }
        ++j;
      }

      if (np1 == 0) ans += z * exp(r);
    }

    printf("%.10f\n", (double)ans);
  }

  return 0;
}

