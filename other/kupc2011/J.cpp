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

const int dx[8] = {-1, -2, -2, -1, +1, +2, +2, +1};
const int dy[8] = {-2, -1, +1, +2, +2, +1, -1, -2};

int H, W;
int fld[60][20];

int countit(int x, int y, int bx, int by) {  // (x, y):center, [(by, bx), (H-1, W-1)]:range
  int res = 0;
  rep (d, 8) {
    int tx = x + dx[d];
    int ty = y + dy[d];
    if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
    if (mp(ty, tx) < mp(by, bx)) continue;
    ++res;
  }
  return res;
}

int search(int x, int y) {
  if (x >= W) return search((x + 1) % 2, y + 1);
  if (y >= H) return 1;

  int res = 0;

  rep (p, 2) {  // p <=> place
    bool ok = true;
    rep (d, 8) {
      int tx = x + dx[d];
      int ty = y + dy[d];
      if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
      fld[ty][tx] = (fld[ty][tx] + p) % 3;
      if (countit(tx, ty, x, y) == 1 && fld[ty][tx] != 0) ok = false;
    }

    if (ok) res += search(x + 2, y);

    rep (d, 8) {
      int tx = x + dx[d];
      int ty = y + dy[d];
      if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
      fld[ty][tx] = (fld[ty][tx] - p + 3) % 3;
    }
  }

  return res;
}

int main() {
  scanf("%d%d", &H, &W);
  int z = 0;
  rep (y, H) rep (x, W) {
    scanf("%d", &fld[y][x]);
    if (fld[y][x] == 0) ++z;
  }

  if ((H == 1 || W == 1)) {
    printf("%d\n", int(((long long)(z == W * H ? 1 : 0) << (W * H)) % 1000000007));
  } else {
    rep (y, H) rep (x, W) {
      if (countit(x, y, 0, 0) == 0 && fld[y][x] != 0) {
        puts("0");  // No chance
        return 0;
      }
    }

    printf("%d\n", search(0, 0) * search(1, 0));
  }

  return 0;
}

