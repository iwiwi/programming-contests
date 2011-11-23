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

string fld[110];
int dp[110][110];

int main() {
  int H, W;
  while (cin >> H >> W) {
    rep (y, H) cin >> fld[y];

    rep (y, H) rep (x, W) dp[y][x] = INF;
    dp[0][0] = 0;
    rep (y, H) rep (x, W) {
      dp[y][x] += fld[y][x] - '0';
      dp[y + 1][x] = min(dp[y + 1][x], dp[y][x]);
      dp[y][x + 1] = min(dp[y][x + 1], dp[y][x]);
    }

    printf("%d\n", dp[H - 1][W - 1]);
  }
  return 0;
}
