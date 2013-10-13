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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

char F[510][510];
bool vis[510][510];

vector<tuple<char, int, int> > ans;

void doit(int sx, int sy) {
  vector<pair<int, int> > stk, ord;
  stk.emplace_back(sx, sy);
  vis[sy][sx] = true;

  while (!stk.empty()) {
    int x, y;
    tie(x, y) = stk.back();
    stk.pop_back();
    ord.emplace_back(x, y);

    rep (d, 4) {
      int tx = x + dx[d], ty = y + dy[d];
      if (F[ty][tx] == '#' || vis[ty][tx]) continue;
      stk.emplace_back(tx, ty);
      vis[ty][tx] = true;
    }
  }

  rep (i, ord.size()) {
    ans.emplace_back('B', ord[i].first, ord[i].second);
  }
  reverse(all(ord));
  rep (i, ord.size() - 1) {
    ans.emplace_back('D', ord[i].first, ord[i].second);
    ans.emplace_back('R', ord[i].first, ord[i].second);
  }
}

int main() {
  int H, W;
  while (2 == scanf("%d%d", &H, &W)) {
    memset(F, '#', sizeof(F));
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) scanf(" %c", &F[y][x]);
    }

    memset(vis, 0, sizeof(vis));
    ans.clear();
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        if (F[y][x] == '.' && !vis[y][x]) doit(x, y);
      }
    }

    printf("%d\n", (int)ans.size());
    rep (i, ans.size()) printf("%c %d %d\n", get<0>(ans[i]), get<2>(ans[i]), get<1>(ans[i]));
  }
}
