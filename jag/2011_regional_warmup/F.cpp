#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

int H, W, N;
char S[1000010];
char fld[1010][1010];

int ds[1000010];
int nxt[1000010][4];

int pot[1010][1010][4];

typedef pair<pair<int, int>, pair<int, int> > piiii;
priority_queue<piiii, vector<piiii>, greater<piiii> > que;

int main() {
  for (;;) {
    scanf("%d%d%d", &H, &W, &N);
    if (W == 0 && H == 0 && N == 0) return 0;
    scanf("%s", S);
    rep (y, H) scanf("%s", fld[y]);

    rep (d, 4) nxt[N][d] = -1;
    ds[N] = 0;
    for (int p = N - 1; p >= 0; --p) {
      ds[p] = ds[p + 1] + (S[p] == 'L' ? -1 : +1);
      ds[p] = (ds[p] + 4) % 4;

      rep (d, 4) nxt[p][d] = nxt[p + 1][d];
      nxt[p][ds[p + 1]] = p + 1;
    }

    que = priority_queue<piiii, vector<piiii>, greater<piiii> >();
    rep (y, H) rep (x, W) {
      rep (d, 4) pot[y][x][d] = INT_MAX;
      if (fld[y][x] == 'S') {
        int d = 1;  // north
        que.push(mp(mp(0, d), mp(x, y)));
        pot[y][x][d] = 0;
      }
    }

    while (!que.empty()) {
      int p = que.top().first.first;
      int d = que.top().first.second;
      int x = que.top().second.first;
      int y = que.top().second.second;
      if (p > pot[y][x][d]) continue;
      que.pop();

      if (fld[y][x] == 'G') {
        puts("Yes");
        goto done;
      }
      if (fld[y][x] == '#') continue;

      // Forward
      {
        int tx = x + dx[d];
        int ty = y + dy[d];
        int td = d, tp = p;
        if (tx < 0 || W <= tx || ty < 0 || H <= ty) goto ng;
        if (tp >= pot[ty][tx][td]) goto ng;
        que.push(mp(mp(tp, td), mp(tx, ty)));
        pot[ty][tx][td] = tp;
     ng:;
      }

      // LR
      for (int dd = -1; dd <= 1; dd += 2) {
        int tx = x, ty = y;
        int td = (d + dd + 4) % 4;
        int tp = nxt[p][(ds[p] + dd + 4) % 4];
        if (tp == -1 || tp >= pot[ty][tx][td]) continue;
        que.push(mp(mp(tp, td), mp(tx, ty)));
        pot[ty][tx][td] = tp;
      }
    }
    puts("No");
 done:;
  }
}
