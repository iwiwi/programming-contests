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

const int dx[8] = {1, 2,  2,  1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1,  1,  2};

int W, H;

int id(int x, int y) {
  return y * W + x;
}

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    int ans = 0;
    if (H * W <= 20) {
      rep (b, 1 << (H * W)) {
        rep (y, H) rep (x, W) {
          if (b & (1 << id(x, y))) {
            rep (d, 8) {
              int tx = x + dx[d];
              int ty = y + dy[d];
              if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
              if (b & (1 << id(tx, ty))) goto ng;
            }
          }
        }
        ans = max(ans, __builtin_popcount(b));
      ng:;
      }
    }
    else if (H == 1 || W == 1) {
      ans = H * W;
    } else if (H == 2 || W == 2) {
      int t = max(H, W);
      switch (t % 4) {
      case 0: ans = t + 0; break;
      case 1: ans = t + 1; break;
      case 2: ans = t + 2; break;
      case 3: ans = t + 1; break;
      }
    } else {
      ans = (W * H + 1) / 2;
    }

    printf("%d\n", ans);
  }

  return 0;
}

