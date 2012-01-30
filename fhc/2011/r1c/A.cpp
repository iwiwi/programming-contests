#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <cassert>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int W, H;
char fld[110][110];

int pot[110][110];

int main() {
  int N;
  scanf("%d", &N);

  rep (ca, N) {
    fprintf(stderr, "%d / %d\n", ca, N);

    scanf("%d%d", &H, &W);
    rep (y, H) scanf("%s", fld[y]);

    queue<int> quex, quey;
    memset(pot, -1, sizeof(pot));

    vector<int> colx[20], coly[20];
    rep (y, H) rep (x, W) {
      if (fld[y][x] == 'S') {
        quex.push(x);
        quey.push(y);
        pot[y][x] = 0;
      }
      else {
        if ('1' <= fld[y][x] && fld[y][x] <= '9') {
          colx[fld[y][x] - '0'].push_back(x);
          coly[fld[y][x] - '0'].push_back(y);
        }
      }
    }

    while (!quex.empty()) {
      int x = quex.front(); quex.pop();
      int y = quey.front(); quey.pop();

      if (fld[y][x] == 'E') {
        printf("%d\n", pot[y][x]);
        goto done;
      }

      rep (d, 4) {
        int tx = x + dx[d];
        int ty = y + dy[d];
        if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
        if (fld[ty][tx] == 'W') continue;
        if (pot[ty][tx] == -1) {
          quex.push(tx);
          quey.push(ty);
          pot[ty][tx] = pot[y][x] + 1;
        }
      }

      if ('1' <= fld[y][x] && fld[y][x] <= '9') {
        int k = fld[y][x] - '0';
        rep (j, colx[k].size()) {
          int tx = colx[k][j];
          int ty = coly[k][j];
          if (pot[ty][tx] == -1) {
            quex.push(tx);
            quey.push(ty);
            pot[ty][tx] = pot[y][x] + 1;
          }
        }
        colx[k].clear();
      }
    }
    assert(false);
 done:;
  }

  return 0;
}
