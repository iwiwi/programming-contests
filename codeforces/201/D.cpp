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

int N, M, K;
char A[20][20];
char B[500010][20];

int next[500010][20];
int dp[1 << 15][110];

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%s", A[i]);
    scanf("%d", &M);

    int L = N * (N - 1) / 2;

    pair<int, int> ans = mp(L + 1, -1);
    rep (iter, M) {
      scanf("%d", &K);
      rep (i, K) scanf("%s", B[i]);

      rep (i, N) {
        int t = K;
        next[K][i] = K;
        for (int j = K - 1; j >= 0; --j) {
          if (strcmp(A[i], B[j]) == 0) t = j;
          next[j][i] = t;
        }
      }

      rep (b, 1 << N) rep (l, L + 1) dp[b][l] = K;
      dp[0][0] = -1;

      rep (b, 1 << N) rep (l, L + 1) {
        if (dp[b][l] == K) continue;

        int tl = l;
        for (int i = N - 1; i >= 0; --i) {
          if (b & (1 << i)) ++tl;
          else {
            int tb = b | 1 << i;
            dp[tb][tl] = min(dp[tb][tl], next[dp[b][l] + 1][i]);
          }
        }
      }

      int mi = 999;
      rep (l, L + 1) if (dp[(1 << N) - 1][l] < K) mi = min(mi, l);
      ans = min(ans, mp(mi, iter));
    }

    if (ans.first <= L) {
      printf("%d\n", ans.second + 1);
      int p = N * (N - 1) / 2 - ans.first + 1;
      printf("[:%s:]\n", string(p, '|').c_str());
    } else {
      puts("Brand new problem!");
    }
  }

  return 0;
}

