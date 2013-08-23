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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef pair<int, int> pii;

const int W = 12, H = 12;

enum {UP, RIGHT, DOWN, LEFT};
const int dx[4] = { 0, +1,  0, -1};
const int dy[4] = {-1,  0, +1,  0};

namespace greedy {
int B[20][20];  // Board
bool fix[20][20];  // Fixed

vector<vector<int> > bfs(int x, int y) {
  vector<vector<int> > dst(20, vector<int>(20, -1));

  queue<pair<int, int> > que;
  que.push(mp(x, y));
  dst[y][x] = 0;

  while (!que.empty()) {
    int x = que.front().first;
    int y = que.front().second;
    que.pop();
    rep (d, 4) {
      int tx = x + dx[d], ty = y + dy[d];
      if (fix[ty][tx] || dst[ty][tx] != -1) continue;
      que.push(mp(tx, ty));
      dst[ty][tx] = dst[y][x] + 1;
    }
  }

  return dst;
}

vector<pair<int, int> > move_any_empty(int x, int y) {
  vector<vector<int> > dst = bfs(x, y);

  int bx = -1, by = -1, bd = INT_MAX;
  for (int ty = 1; ty <= H; ++ty) {
    for (int tx = 1; tx <= W; ++tx) {
      if (dst[ty][tx] != -1 && B[ty][tx] == 0) {
        if (dst[ty][tx] < bd) {
          bx = tx;
          by = ty;
          bd = dst[ty][tx];
        }
      }
    }
  }

  vector<pair<int, int> > tmp;
  while (mp(bx, by) != mp(x, y)) {
    rep (d, 4) {
      int tx = bx + dx[d], ty = by + dy[d];
      if (dst[ty][tx] == dst[by][bx] - 1) {
        assert(B[ty][tx] != 0);
        tmp.pb(mp(B[ty][tx], (d + 2) % 4));
        swap(B[ty][tx], B[by][bx]);
        bx = tx;
        by = ty;
        goto done;
      }
    }
    assert(false);
 done:;
  }

  return tmp;
}

vector<pair<int, int> > solve_one(int k) {
  vector<pair<int, int> > ans;

  int sx = 1 + (k - 1) % 12, sy = 1 + (k - 1) / 12;

  bool wall3 = false;
  if (fix[sy][sx - 1] && fix[sy][sx + 1]) wall3 = true;
  if (wall3) {
    vector<pair<int, int> > tmp = move_any_empty(sx, sy);
    ans.insert(ans.end(), all(tmp));
    fix[sy][sx] = true;
    ++sy;
  }

  int cx = -1, cy = -1;
  for(int y = 1; y <= H; ++y) for (int x = 1; x <= W; ++x) if (B[y][x] == k) { cx = x; cy = y; }

  vector<vector<int> > dst = bfs(sx, sy);
  while (mp(cx, cy) != mp(sx, sy)) {
    // fprintf(stderr, "%d: %d %d (%d <- %d %d)\n", k, cx, cy, dst[cy][cx], sx, sy);
    rep (d, 4) {
      int tx = cx + dx[d], ty = cy + dy[d];
      if (dst[ty][tx] == dst[cy][cx] - 1) {
        fix[cy][cx] = true;
        vector<pair<int, int> > tmp = move_any_empty(tx, ty);
        fix[cy][cx] = false;
        ans.insert(ans.end(), all(tmp));
        assert(B[cy][cx] == k && B[ty][tx] == 0);

        ans.pb(mp(k, d));
        swap(B[cy][cx], B[ty][tx]);

        cx = tx;
        cy = ty;
        goto done;
      }
    }
    assert(false);
 done:;
  }

  if (wall3) {
    assert(B[sy - 1][sx] == 0 && B[sy][sx] == k);
    ans.pb(mp(k, int(UP)));
    swap(B[sy - 1][sx], B[sy][sx]);
  }
  return ans;
}

vector<pair<int, int> > solve() {
  memset(fix, 1, sizeof(fix));
  for (int y = 1; y <= H; ++y) for (int x = 1; x <= W; ++x) fix[y][x] = false;

  vector<pair<int, int> > ans;
  for (int k = 1; k <= 123; ++k) {
    vector<pair<int, int> > tmp = solve_one(k);
    ans.insert(ans.end(), all(tmp));
    int sx = 1 + (k - 1) % 12, sy = 1 + (k - 1) / 12;
    fix[sy][sx] = true;
    assert(B[sy][sx] == k);
    fprintf(stderr, "FIX %d %d\n", sx, sy);

    /*
    for (int tk = k + 1; tk <= k + 13 && tk <= 123; ++tk) {
      int x = 1 + (tk - 1) % 12, y = 1 + (tk - 1) / 12;
      tmp = move_any_empty(x, y);
      ans.insert(ans.end(), all(tmp));
      fix[y][x] = true;
    }
    for (int tk = k + 1; tk <= k + 13 && tk <= 123; ++tk) {
      int x = 1 + (tk - 1) % 12, y = 1 + (tk - 1) / 12;
      fix[y][x] = false;
    }
    */
  }
  return ans;
}
}

int main() {
  int B[20][20];
  for (int y = 1; y <= H; ++y) for (int x = 1; x <= W; ++x) scanf("%d", &B[y][x]);

  for (int y = 1; y <= H; ++y) for (int x = 1; x <= W; ++x) greedy::B[y][x] = B[y][x];
  vector<pii> ans = greedy::solve();

  printf("%d\n", (int)ans.size());
  const char *move_name[] = {"up", "right", "down", "left"};
  rep (i, ans.size()) printf("%d %s\n", ans[i].first, move_name[ans[i].second]);

  return 0;
}

