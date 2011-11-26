#include <cstdio>
#include <queue>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int H, W;
bool done[1010][1010];
int fld[1010][1010];

int main() {
  scanf("%d%d", &H, &W);

  queue<int> quex, quey;
  rep (y, H) {
    rep (x, W) {
      char c;
      scanf(" %c", &c);
      if (c == 'X') {
        quex.push(x);
        quey.push(y);
        done[y][x] = true;
      }
    }
  }

  int ans = 0;
  while (!quex.empty()) {
    ++ans;
    int x = quex.front(); quex.pop();
    int y = quey.front(); quey.pop();
    rep (d, 4) {
      int tx = x + dx[d];
      int ty = y + dy[d];
      if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
      if (++fld[ty][tx] == 2 && !done[ty][tx]) {
        quex.push(tx);
        quey.push(ty);
        done[ty][tx] = true;
      }
    }
  }

  printf("%d\n", ans);
  return 0;
}
