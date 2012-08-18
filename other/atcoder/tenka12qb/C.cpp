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

int N;
int S[20], T[20];

bool ok[1 << 16];
int dp[1 << 16];

int read_time() {
  int h, m;
  scanf("%d:%d", &h, &m);
  return h * 60 + m;
}

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) {
      S[i] = read_time();
      T[i] = read_time();
    }

    rep (b, 1 << N) {
      ok[b] = true;
      rep (i, N) rep (j, i) if ((b & (1 << i)) && (b & (1 << j))) {
        int s1 = S[i], t1 = T[i];
        int s2 = S[j], t2 = T[j];
        if (s2 < s1) { swap(s1, s2); swap(t1, t2); }
        if (s2 < t1) ok[b] = false;
        if (s1 + 24 * 60 < t2) ok[b] = false;
      }
    }

    rep (b, 1 << N) {
      dp[b] = b == 0 ? 0 : 99999;

      int super = b;
      int sub = super;
      do {
        sub = (sub - 1) & super;
        if (ok[sub]) dp[b] = min(dp[b], 1 + dp[b - sub]);
      } while (sub != super);
    }

    printf("%d\n", dp[(1 << N) - 1]);
  }

  return 0;
}

