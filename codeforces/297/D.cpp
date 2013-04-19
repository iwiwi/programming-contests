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

int H, W, K;
bool R[1010][1010];  // Right
bool D[1010][1010];  // Down

bool ans[1010][1010];

void row(int y, int c0) {
  ans[y][0] = c0;
  for (int x = 1; x < W; ++x) ans[y][x] = ans[y][x - 1] ^ R[y][x - 1];
}

int main() {
  while (3 == scanf("%d%d%d", &H, &W, &K)) {
    // Input
    bool mir = H > W;
    rep (y, H) {
      char t;
      rep (x, W - 1) {
        scanf(" %c", &t);
        (mir ? D[x][y] : R[y][x]) = (t == 'N');
      }
      if (y + 1 < H) {
        rep (x, W) {
          scanf(" %c", &t);
          (mir ? R[x][y] : D[y][x]) = (t == 'N');
        }
      }
    }
    if (mir) swap(W, H);

    // Construct
    if (K == 1) {
      memset(ans, 0, sizeof(ans));
      int cnt[2] = {};
      rep (y, H) rep (x, W - 1) ++cnt[R[y][x]];
      rep (x, W) rep (y, H - 1) ++cnt[D[y][x]];
      if (cnt[1] * 4 > cnt[0] + cnt[1]) goto no;
    } else {
      // 1st row
      row(0, 0);

      for (int y = 1; y < H; ++y) {
        row(y, 0);
        int ng = 0;
        rep (x, W) ng += (D[y - 1][x] != (ans[y - 1][x] != ans[y][x]));
        if (ng > W / 2) row(y, 1);
      }
    }

    // Output
    if (mir) {
      swap(W, H);
    }
    puts("YES");
    rep (y, H) rep (x, W) printf("%d%c", int(mir ? ans[x][y] : ans[y][x]) + 1, x == W - 1 ? '\n' : ' ');
    continue;
 no:
    puts("NO");
  }

  return 0;
}

