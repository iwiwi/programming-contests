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

int fld0[510][510];
int fld1[510][510];

int sumv[510][510];

int main() {
  int H, W, K;
  while (3 == scanf("%d%d%d", &H, &W, &K)) {
    rep (y, H) rep (x, W) {
      char c;
      scanf(" %c", &c);
      fld0[y][x] = c - '0';
    }

    for (int y = 1; y < H; ++y) {
      for (int x = 1; x < W; ++x) {
        int s = 0;
        for (int dx = -1; dx <= 1; ++dx) {
          for (int dy = -1; dy <= 1; ++dy) {
            if (abs(dx) + abs(dy) <= 1) {
              s += fld0[y + dy][x + dx];
            }
          }
        }
        fld1[y - 1][x - 1] = s == 5 ? 1 : 0;
      }
    }

    H -= 2;
    W -= 2;
    rep (x, W) {
      sumv[0][x] = 0;
      rep (y, H) sumv[y + 1][x] = sumv[y][x] + fld1[y][x];
    }

    ll ans = 0;

    for (int ylb = 0; ylb < H; ++ylb) {
      for (int yub = ylb + 1; yub <= H; ++yub) {
        // [ylb, yub) * [xlb, xub)
        int xub = 0, s = 0;
        for (int xlb = 0; xlb < W; ++xlb) {
          while (xub < W && s < K) {
            s += sumv[yub][xub] - sumv[ylb][xub];
            ++xub;
          }
          if (s >= K) ans += W - xub + 1;
          s -= sumv[yub][xlb] - sumv[ylb][xlb];
        }
      }
    }

    // rep (y, H) rep (x, W) printf("%d ", fld1[y][x]); puts("");
    cout << ans << endl;
  }

  return 0;
}

