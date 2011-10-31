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

ll MOD = 1000000 + 3;

ll dp[1010];

int main() {
  int N;
  scanf("%d", &N);

  dp[0] = 1;
  for (int i = 1; i <= N; ++i) {
    ll k = 1;
    dp[i] = 0;
    for (int j = i - 1; j >= 0; --j) {
      dp[i] += (k * dp[j]) % MOD;
      dp[i] %= MOD;
      k = (k * 2) % MOD;
    }
    // printf("%lld\n", dp[i]);
  }

  cout << dp[N] << endl;

  return 0;
}

