#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstdio>
#include <vector>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int H, W, SY, SX, GY, GX;

int yoko[110][110];
int tate[110][110];
int pot[110][110];

int weight(int y1, int x1, int y2, int x2) {
  if (y1 == y2) return yoko[y1][min(x1, x2)];
  else          return tate[min(y1, y2)][x1];
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d%d%d%d%d", &H, &W, &SY, &SX, &GY,&GX);
    if (H == 0 && W == 0) return 0;
    printf("Case %d: ", ca);
    --SY; --SX;
    --GY; --GX;
    
    rep (y, H) {
      rep (x, W - 1) scanf("%d", &yoko[y][x]);
      if (y + 1 < H) rep (x, W) scanf("%d", &tate[y][x]);
    }

    rep (y, H) rep (x, W) pot[y][x] = INT_MAX;
    multimap<int, pair<int, int> > que;
    
    que.insert(mp(0, mp(SY, SX)));
    pot[SY][SX] = 0;
    while (!que.empty()) {
      int p = que.begin()->first;
      int y = que.begin()->second.first;
      int x = que.begin()->second.second;
      que.erase(que.begin());
      if (p > pot[y][x]) continue;

      // printf("%d: %d %d\n", p, y, x);
      
      if (y == GY && x == GX) {
        printf("%d\n", p);
        goto done;
      }

      rep (d, 4) {
        int cy = y, cx = x;
        vector<int> ds;
        int dsum = 0;
        for (;;) {
          int ny = cy + dy[d];
          int nx = cx + dx[d];
          if (ny < 0 || H <= ny || nx < 0 || W <= nx) break;
          int d = weight(cy, cx, ny, nx);
          if (d == 0) break;
          ds.push_back(d);
          dsum += d;
          int td = dsum + d + (ds.size() >= 2 ? ds.front() : 0);
          int tp = p + td;
          if (tp < pot[ny][nx]) {
            pot[ny][nx] = tp;
            que.insert(mp(tp, mp(ny, nx)));
          }

          cy = ny; cx = nx;
        }
      }
    }
    puts("Impossible");
  done:;
  }
}
