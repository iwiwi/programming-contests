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
  int T;
  scanf("%d", &T);
  while (T--) {
    int N, K;
    scanf("%d%d", &N, &K);
    vector<pair<int, int> > X(N);
    rep (i, N) {
      scanf("%d", &X[i].first);
      X[i].second = 1;
    }

    int ans = 0;
    for (;;) {
      // Join!!
      while (X.size() >= 2 &&
             X[X.size() - 2].first + X[X.size() - 2].second == X.back().first) {
        int n = X.back().second;
        X.pop_back();
        X.back().second += n;
      }
      // rep (i, X.size()) printf("(%d, %d) ", X[i].first, X[i].second); puts("");
      if (X.size() == 1 && X.back().first == 1) break;

      // Move!!
      int rn = 0, rp = 0;
      if (X.back().second > K) {
        rn = X.back().second - K;
        rp = X.back().first + K;
        X.back().second = K;
      }
      --X.back().first;
      if (rn > 0) X.push_back(mp(rp, rn));

      ++ans;
    }

    printf("%d\n", ans);
  }

  return 0;
}

