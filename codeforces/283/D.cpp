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

int N;
ll A[5010];
int div2[5010];

int dp[5010];

int main() {
  while (cin >> N) {
    rep (i, N) cin >> A[i];
    reverse(A, A + N);

    rep (i, N) {
      int x;
      for (x = 0; A[i] % (1LL << x) == 0; ++x);
      div2[i] = x - 1;
      // assert(A[i] % (1LL << div2[i]) == 0 && A[i] % (1LL << (1 + div2[i])) != 0);
    }

    int ans = N;
    rep (i, N) {
      dp[i] = i;
      for (int j = 0; j < i; ++j) {
        // A[j], *, *, ..., *, A[i]
        ll y = A[j] / (1LL << min(i - j, div2[j]));
        if (A[i] % y != 0) continue;
        if (i - j <= div2[j] && (A[i] / y) % 2 == 0) continue;

        dp[i] = min(dp[i], dp[j] + (i - j - 1));
      }
      ans = min(ans, dp[i] + (N - i - 1));
    }
    printf("%d\n", ans);
  }

  return 0;
}

