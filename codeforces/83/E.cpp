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

const int INF = 987654321;

int N, L, A[200010];
int dp[21][1 << 20];

int main() {
  while (1 == scanf("%d", &N)) {
    char buf[30];
    rep (i, N) {
      scanf("%s", buf);
      A[i] = 0;
      for (L = 0; buf[L]; ++L) A[i] = A[i] << 1 | (buf[L] == '1');
    }

    for (int l = 0; l <= L; ++l) rep (b, 1 << l) dp[l][b] = INF;
    dp[0][0] = 0;
    int base = L;

    for (int i = 1; i < N; ++i) {
      int mi = INF;  // (i-1, i)
      for (int l = 0; l <= L; ++l) {
        mi = min(mi, dp[l][A[i] >> (L - l)] + base + (L - l));
      }

      int p;
      for (p = 0; p < L; ++p) {
        int msk = (1 << (L - p)) - 1;
        if ((A[i - 1] ^ (A[i] >> p)) & msk) continue;
        else break;
      }
      base += p;

      for (int l = 0; l <= L; ++l) {
        int &t = dp[l][A[i - 1] & ((1 << l) - 1)];
        t = min(t, mi - base);
      }
    }

    printf("%d\n", dp[0][0] + base);
  }

  return 0;
}

