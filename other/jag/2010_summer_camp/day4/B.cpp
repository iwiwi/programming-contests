#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

const char *dirs = "RDLU";

int H, W, N;
char fld[20][20];
string ans;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

bool dfs(int x, int y, int d, int n) {
  if (n == N) {
    return true;
  }
  
  char tmp = '.';
  swap(tmp, fld[y][x]);
  for (int dd = -1; dd <= 1; ++dd) {
    int td = (d + dd + 4) % 4;
    int tx = x, ty = y;
    for (;;) {
      tx += dx[td];
      ty += dy[td];
      if (tx < 0 || W <= tx) break;
      if (ty < 0 || H <= ty) break;
      if (fld[ty][tx] != '.') {
        if (dfs(tx, ty, td, n + 1)) {
          ans += dirs[td];
          return true;
        }
        break;
      }
    }
  }
  swap(tmp, fld[y][x]);
  return false;
}

int main() {
  scanf("%d%d", &H, &W);
  rep (y, H) scanf("%s", fld[y]);

  int sx, sy, sd;
  rep (y, H) rep (x, W) {
    if (isupper(fld[y][x])) {
      sx = x;
      sy = y;
      sd = strchr(dirs, fld[y][x]) - dirs;
    }
    else if (fld[y][x] == 'o') {
      ++N;
    }
  }

  dfs(sx, sy, sd, 0);
  reverse(ans.begin(), ans.end());
  cout << ans << endl;
  return 0;
}
