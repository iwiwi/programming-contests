#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>
#include <set>
#include <utility>
#include <cstring>
#include <queue>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int N, M, W;

char fld[10][10];
char hol[10][10];

bool stop[4][10][10];

string enc() {
  string r(N * N, ' ');
  rep (y, N) rep (x, N) r[y * N + x] = fld[y][x];
  return r;
}

void dec(const string &e) {
  rep (y, N) rep (x, N) fld[y][x] = e[y * N + x];
}

bool move(int d) {
  bool exist[10] = {0};
  rep (y, N) rep (x, N) if (fld[y][x] != ' ') exist[fld[y][x] - '0'] = true;
  char thol[10][10];
  rep (y, N) rep (x, N) {
    thol[y][x] = hol[y][x];
    if (thol[y][x] != ' ' && !exist[thol[y][x] - '0']) {
      thol[y][x] = ' ';
    }
  }
 
  bool up;
  do {
    up = false;
    rep (y, N) rep (x, N) {
      if (fld[y][x] == ' ') continue;
      if (stop[d][y][x]) continue;
      
      int tx = x + dx[d];
      int ty = y + dy[d];
      if (tx < 0 || N <= tx || ty < 0 || N <= ty) continue;
      if (fld[ty][tx] != ' ') continue;
      swap(fld[y][x], fld[ty][tx]);
      
      if (thol[ty][tx] != ' ') {
        if (thol[ty][tx] == fld[ty][tx]) thol[ty][tx] = fld[ty][tx] = ' ';
        else return false;
      }
      up = true;
    }
  } while (up);
  return true;
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d%d", &N, &M, &W);
    if (N == 0 && M == 0 && W == 0) return 0;

    memset(fld, ' ', sizeof(fld));
    rep (i, M) {
      int y, x;
      scanf("%d%d", &y, &x);
      fld[y][x] = '0' + i;
    }
    memset(hol, ' ', sizeof(hol));
    rep (i, M) {
      int y, x;
      scanf("%d%d", &y, &x);
      hol[y][x] = '0' + i;
    }

    bool ng = false;
    rep (y, N) rep (x, N) {
      if (fld[y][x] != ' ' && hol[y][x] != ' ') {
        if (fld[y][x] == hol[y][x]) fld[y][x] = ' ';
        else ng = true;
      }
    }
    if (ng) {
      printf("Case %d: impossible\n\n", ca);
      continue;
    }

    memset(stop, 0, sizeof(stop));
    rep (i, W) {
      pair<int, int> a, b;
      scanf("%d%d%d%d", &a.first, &a.second, &b.first, &b.second);
      if (a > b) swap(a, b);
      if (a.first < b.first) {
        stop[1][a.first][a.second] = true;
        stop[3][b.first][b.second] = true;
      }
      else {
        stop[0][a.first][a.second] = true;
        stop[2][b.first][b.second] = true;
      }
    }

    map<string, int> mem;
    queue<string> que;
    string e = enc();
    mem[e] = 0;
    que.push(e);

    while (!que.empty()) {
      string e = que.front();
      int c = mem[e];
      que.pop();

      if (count(e.begin(), e.end(), ' ') == N * N) {
        // printf("Case %d: %d %s\n\n", ca, c, c == 1 ? "move" : "moves");
        printf("Case %d: %d moves\n\n", ca, c);
        goto done;
      }

      rep (d, 4) {
        dec(e);
        if (!move(d)) continue;
        string te = enc();
        if (mem.count(te)) continue;
        mem[te] = c + 1;
        que.push(te);
      }
    }
    printf("Case %d: impossible\n\n", ca);
  done:;
  }
}
