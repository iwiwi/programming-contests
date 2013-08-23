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
int H, W, A, B;

map<int, int> mem[10][10][70][70];

int search(int x, int y, int m, int a, int b) {
  if (x == W) return search(0, y + 1, m, a, b);
  if (y == H) return a >= A && b <= B ? 0 : -INF;
  if (mem[y][x][a][b].count(m)) return mem[y][x][a][b][m];

  int ans = -INF;
  rep (k, 4) {
    int tm = m;
    tm &= (1 << W) - 1 - (1 << x);
    tm |= (k % 2) << x;  // DOWN(x)
    tm |= (k / 2) << W;  // RIGHT

    int straight = 0, deko = 0, boko = 0;
    ++(y == 0     ? straight : (( m & (1 << x)) ? boko : deko));  // UP
    ++(x == 0     ? straight : (( m & (1 << W)) ? boko : deko));  // LEFT
    ++(y == H - 1 ? straight : ((tm & (1 << x)) ? deko : boko));  // DOWN
    ++(x == W - 1 ? straight : ((tm & (1 << W)) ? deko : boko));  // RIGHT

    int ta = a + (boko == 4 ? 1 : 0);
    int tb = b + (deko == 4 ? 1 : 0);
    int tc = (straight == 1 && boko == 3 ? 1 : 0);
    ans = max(ans, tc + search(x + 1, y, tm, ta, tb));
  }
  return mem[y][x][a][b][m] = ans;
}

int main() {
  while (4 == scanf("%d%d%d%d", &H, &W, &A, &B)) {
    rep (x, W) rep (y, H) rep (a, 70) rep (b, 70) mem[y][x][a][b].clear();
    printf("%d\n", search(0, 0, 0, 0, 0));
  }

  return 0;
}

