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
typedef unsigned int uint;

const int MOD = 1000000007;
const int MAX = 1000000010;

int dp[1 << 24];

int main() {
  int N, A[30];
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", &A[i]);

    int K, B[5] = {};
    scanf("%d", &K);
    rep (i, K) scanf("%d", &B[i]);

    dp[0] = 1;
    for (int b = 1; b < (1 << N); ++b) {
      uint s = 0, t = 0;

      {
        int i = 0;
        for (; i + 3 < N; i += 4) {
          s += (b & (1 << i)) ? A[i + 0] : 0; t += (b & (1 << i)) ? dp[b ^ (1 << i)] : 0;
          s += (b & (2 << i)) ? A[i + 1] : 0; t += (b & (2 << i)) ? dp[b ^ (2 << i)] : 0;
          s += (b & (4 << i)) ? A[i + 2] : 0; t += (b & (4 << i)) ? dp[b ^ (4 << i)] : 0;
          s += (b & (8 << i)) ? A[i + 3] : 0; t += (b & (8 << i)) ? dp[b ^ (8 << i)] : 0;

          s = s < uint(MAX) ? s : MAX;
          t = t < uint(MOD) ? t : t % uint(MOD);
        }
        for (; i < N; ++i) {
          s += (b & (1 << i)) ? A[i + 0] : 0;
          t += (b & (1 << i)) ? dp[b ^ (1 << i)] : 0;
          s = s < uint(MAX) ? s : MAX;
          t = t < uint(MOD) ? t : t - uint(MOD);
        }
      }

      if (B[0] == (int)s || B[1] == (int)s) dp[b] = 0;
      else dp[b] = t % MOD;
    }

    printf("%d\n", dp[(1 << N) - 1]);
  }
}

