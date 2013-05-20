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

typedef long long ll;
const int K = 10010;

ll dp[K];

int main() {
  int T;
  scanf("%d", &T);
  rep (t, T) {
    int N;
    scanf("%d", &N);

    memset(dp, 0, sizeof(dp));
    int max_k = 1;
    rep (i, N) {
      int x;
      scanf("%d", &x);
      for (int k = 1; k <= max_k; ++k) if (dp[k]) dp[__gcd(k, x)] += dp[k];
      ++dp[x];
      max_k = max(max_k, x);
    }
    cout << dp[1] << endl;
  }

  return 0;
}
