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
#include <numeric>
using namespace std;
 
#define all(c) (c).begin(), (c).end() 
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

const ll MOD = 1000000007;

inline ll mod(ll a, ll m = MOD) { return (a % m + m) % m; }

// ax = 1 (mod m)
ll inverse(ll a, ll m = MOD) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}






int M, X[110], Y[110];

ll fact[1010];
ll cmb[1010][1010];

ll dp[2][1010];

int main() {
  while (1 == scanf("%d", &M)) {
    rep (i, M) scanf("%d", X + i);
    rep (i, M) scanf("%d", Y + i);
    int S = accumulate(X, X + M, 0);

    cmb[0][0] = 1;
    for (int n = 1; n <= S; ++n) {
      cmb[n][0] = 1;
      for (int i = 1; i <= n; ++i) cmb[n][i] = (cmb[n - 1][i - 1] + cmb[n - 1][i]) % MOD;
    }
    
    fact[0] = 1;
    for (int i = 1; i <= S; ++i) fact[i] = (fact[i - 1] * i) % MOD;

    ll p = fact[S];
    rep (i, M) p = (p * inverse(fact[X[i]])) % MOD;

    memset(dp, 0, sizeof(dp));
    ll *crr = dp[0], *nxt = dp[1];
    crr[0] = p;
    
    rep (i, M) {
      for (int j = 0; j <= S; ++j) nxt[j] = 0;
      
      for (int j = 0; j + X[i] <= S; ++j) {
        int t = j + X[i];
        
        int kub = min(Y[i], t);
        for (int k = 0; k <= kub; ++k) {
          nxt[t - k] += (crr[j] * cmb[t][k]) % MOD;
          nxt[t - k] %= MOD;
        }
      }
      
      swap(crr, nxt);
    }

    cout << crr[0] << endl;
  }
  
  return 0;
}

