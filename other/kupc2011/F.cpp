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

int N, K;
double dp[1510][1510];

int main() {
  while (2 == scanf("%d%d", &N, &K)) {
    vector<pair<double, double> > org;
    rep (i, N) {
      int x, y, r;
      scanf("%d%d%d", &x, &y, &r);

      double d = sqrt(x * x + y * y);
      double th = asin(r / d);
      double a = atan2(y, x);
      if (y < 0 && x < 0) {
        a += 2 * M_PI;
      }

      double bgn = min(max(a - th, 0.0), M_PI);
      double end = min(max(a + th, 0.0), M_PI);
      // printf("[%f, %f] : %f\n", bgn ,end, (end - bgn) / M_PI);
      org.pb(mp(bgn, end));
    }
    sort(all(org));

    vector<pair<double, double> > itv;
    rep (i, org.size()) {
      if (!itv.empty() && org[i].second <= itv.back().second) continue;
      itv.pb(org[i]);
    }
    itv.insert(itv.begin(), mp(-1.0, -1.0));  // dummy;
    N = itv.size();

    memset(dp, 0, sizeof(dp));
    int seg = 0;
    for (int i = 1; i < N; ++i) {
      pair<double, double> c = itv[i];
      while (seg + 1 < i && itv[seg + 1].second < c.first) ++seg;
    
      for (int k = 1; k <= K; ++k) {
        double a = dp[seg    ][k - 1] + (c.second - c.first);
        double b = dp[seg + 1][k - 1] + (c.second - itv[seg + 1].second);
        dp[i][k] = max(a, b);

        dp[i][k] = max(dp[i][k], dp[i - 1][k]);
      }
    }

    printf("%.10f\n", dp[N - 1][K] / M_PI);
  }
  return 0;
}
