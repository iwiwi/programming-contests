#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <climits>
#include <iostream>
#include <cassert>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

const int K = 1000000;

vector<pair<int, string> > P;

pair<int, ll> dp[K + 10];

ll push(ll x, int i) {
  return (x << 9) | i;
}


int main() {
  char buf[256];
  
  // High
  {
    ll s = 0;
    for (int i = 1; ; ++i) {
      s += i * i;
      if (s > K) break;
      sprintf(buf, "%dH", i);
      if (i >= 2) P.pb(mp(s, string(buf)));
    }
  }
  // Low
  for (int d = 1; d <= 2; ++d) {
    ll s = 0;
    for (int i = d; ; i += 2) {
      s += i * i;
      if (s > K) break;
      sprintf(buf, "%dL", i);
      if (i >= 3) P.pb(mp(s, string(buf)));
    }
  }
  sort(P.begin(), P.end());
  reverse(P.begin(), P.end());
  // rep (i, P.size()) cout << P[i].first << " " << P[i].second << endl;

  dp[0] = mp(0, 0LL);
  for (int j = 1; j <= K; ++j) dp[j] = mp(INT_MAX, 0LL);
  
  rep (i, P.size()) {
    int p = P[i].first;
    for (int j = K; j >= p; --j) {
      if (dp[j - p].first == INT_MAX) continue;
      dp[j] = min(dp[j],
                  mp(1 + dp[j - p].first, push(dp[j - p].second, i)));
    }
  }

  // int ma = 0;
  // for (int j = 0; j <= K; ++j) {
  //   if (dp[j].first == INT_MAX) continue;
  //   ma = max(ma, dp[j]);
  // }
  // fprintf(stderr, "ma = %d\n", ma);

  // DP
  for (int ca = 1;; ++ca) {
    int C;
    scanf("%d", &C);
    if (C == 0) return 0;
    printf("Case %d:", ca);

    if (dp[C].first == INT_MAX) {
      puts(" impossible");
      continue;
    }

    int k = dp[C].first;

    vector<int> res;
    ll x = dp[C].second;
    rep (i, k) {
      res.pb(x & ((1 << 9) - 1));
      x >>= 9;
    }
    
    reverse(res.begin(), res.end());
    rep (i, k) printf(" %s", P[res[i]].second.c_str());
    puts("");
    
    /*
    int t = C;
    vector<string> ans;
    rep (i, P.size()) {
      int p = P[i].first;
      if (t >= p && dp[t - p] + 1 == dp[t]) {
        ans.pb(P[i].second);
        // printf("%d: %d\n", t ,dp[t]);
        t -= p;
      }
    }
    // assert(t == 0);
    */
    
    // rep (i, ans.size()) printf(" %s", ans[i].c_str());
    // puts("");
  }
}
