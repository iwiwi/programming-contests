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

bool pre[1 << 10][110];

void search(int k, int r, int x, int y, int b) {
  if (x + y > 100) return;
  pre[r][x + y] = true;

  // end
  if (k == 0) search(1, r, 0, x, b);

  // continue
  rep (i, 10) if (b & (1 << i)) search(k, r, x * 10 + i, y, b - (1 << i));
}

int main() {
  rep (b, 1 << 10) search(0, b, 0, 0, b);

  for (int ca = 0; ; ++ca) {
    int N;
    scanf("%d", &N);
    if (N == 0) return 0;

    int A[20];
    rep (i, N) scanf("%d", &A[i]);

    printf("Case %d: ", ca + 1);
    for (int k = 1; k <= 10; ++k) {
      int n = 10;
      for (int m = (1 << k) - 1; m < (1 << n); ) {
        rep (i, N) if (!pre[m][A[i]]) goto ng;
        for (int i = 9; i >= 0; --i) if (m & (1 << i)) printf("%d", i);
        goto done;
     ng:;

        int x = m & -m;
        int y = m + x;
        m = ((m & ~y) / x >> 1) | y;
      }

      rep (b, 1 << 10) {
      }
    }
 done:
    puts("");
  }
}
