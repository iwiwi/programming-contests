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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int H, W, L;
char S[110];
char F[110][110];

int mem[110][110][5][110];

int search(int x, int y, int d, int k) {
  if (x < 0 || W <= x || y < 0 || H <= y) return INF;
  if (mem[x][y][d][k] != -1) return mem[x][y][d][k];
  if (k == L) return 0;

  int res = INF;
  if (S[k] == F[y][x]) {
    // Turn!
    if (k == L - 1) {
      res = 0;
    } else {
      rep (td, 4) if (td != d) {
        res = min(res, 1 + search(x + dx[td], y + dy[td], td, k + 1));
      }
    }
  } else {
    // Advance!
    res = 1 + search(x + dx[d], y + dy[d], d, k);
  }

  return mem[x][y][d][k] = res;
}

int main() {
  while (cin >> H >> W >> L) {
    cin >> S;
    rep (y, H) cin >> F[y];

    memset(mem, -1, sizeof(mem));
    int ans = INF;
    rep (y, H) rep (x, W) rep (d, 4) {
      ans = min(ans, 1 + search(x + dx[d], y + dy[d], d, 0));
    }

    if (ans >= INF) puts("-1");
    else printf("%d\n", ans);
  }

  return 0;
}

