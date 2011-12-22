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
    vector<pair<double, int> > P(N);
    rep (i, N) {
      scanf("%lf", &P[i].first);
      P[i].first /= 100;
      P[i].second = i;
    }
    sort(all(P));

    double best_p = -1.0;
    int best_k = -1;
    for (int k = 0; k <= K; ++k) {
      double p0 = 0.0, p1 = 1.0;
      rep (i, N) if (i < k || N - (K - k) <= i) {
        p0 = p0 * P[i].first + p1 * (1.0 - P[i].first);
        p1 = p1 * P[i].first;
      }
      if (p0 > best_p) {
        best_p = p0;
        best_k = k;
      }
    }

    bool f = true;
    rep (i, N) if (i < best_k || N - (K - best_k) <= i) {
      if (f) f = false;
      else printf(" ");
      printf("%d", P[i].second + 1);
    }
    puts("");
  }

  return 0;
}

