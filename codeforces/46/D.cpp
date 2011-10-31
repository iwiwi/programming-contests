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

int ans[110];

int main() {
  int L, B, F;
  while (3 == scanf("%d%d%d", &L, &B, &F)) {
    int N;
    scanf("%d", &N);

    vector<pair<int, int> > cars;
    rep (q, N) {
      int a, b;
      scanf("%d%d", &a, &b);

      if (a == 1) {
        vector<int> xs;
        xs.pb(0);
        xs.pb(L - b);
        rep (i, cars.size()) {
          xs.pb(cars[i].first + cars[i].second + B);
          xs.pb(cars[i].first - F - b);
        }
        sort(all(xs));
        rep (i, xs.size()) {
          int x = xs[i];
          if (x < 0 || L < x + b) continue;
          rep (j, cars.size()) {
            if (x + b + F <= cars[j].first) continue;
            if (cars[j].first + cars[j].second + B <= x) continue;
            goto ng;
          }
          printf("%d\n", x);
          cars.pb(mp(x, b));
          sort(all(cars));
          // rep (j, cars.size()) printf(" (%d,%d)", cars[j].first, cars[j].second); puts("");
          ans[q] = x;
          goto done;
        ng:;
        }
        puts("-1");
      done:;
      }
      else {
        --b;
        rep (i, cars.size()) {
          if (cars[i].first == ans[b]) {
            cars.erase(cars.begin() + i);
            break;
          }
        }
      }
    }
  }

  return 0;
}

