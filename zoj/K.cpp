#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <deque>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define mp make_pair

typedef long long ll;

int X1[510], Y1[510], X2[510], Y2[510];
bool ng[2010][2010];
int cst[2][2010][2010];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    map<int, int> xid, yid;

    int xs, ys, xt, yt;
    scanf("%d%d%d%d", &xs, &ys, &xt, &yt);
    xs *= 2; ys *= 2; xt *= 2; yt *= 2;

    xid[xs] = xid[xt] = 0;
    yid[ys] = yid[yt] = 0;
    
    rep (i, N) {
      scanf("%d%d%d%d", X1 + i, Y1 + i, X2 + i, Y2 + i);
      X1[i] *= 2; Y1[i] *= 2; X2[i] *= 2; Y2[i] *= 2;

      xid[X1[i] - 1] = xid[X1[i]] = xid[X2[i]] = xid[X2[i] + 1] = 0;
      yid[Y1[i] - 1] = yid[Y1[i]] = yid[Y2[i]] = yid[Y2[i] + 1] = 0;
    }

    int xid_ub = 0, yid_ub = 0;
    tr (xid, ite) ite->second = xid_ub++;
    tr (yid, ite) ite->second = yid_ub++;

    memset(ng, 0, sizeof(ng));
    rep (i, N) {
      int x1 = xid[X1[i]], x2 = xid[X2[i]];
      int y1 = yid[Y1[i]], y2 = yid[Y2[i]];
      for (int x = x1; x <= x2; ++x) ng[y1][x] = ng[y2][x] = true;
      for (int y = y1; y <= y2; ++y) ng[y][x1] = ng[y][x2] = true;
    }

    // be careful!!
    xs = xid[xs]; ys = yid[ys];
    xt = xid[xt]; yt = yid[yt];

    memset(cst, -1, sizeof(cst));
    deque<pair<pair<int, int>, bool> > deq;
    deq.push_back(mp(mp(xs, ys), false));
    deq.push_back(mp(mp(xs, ys), true));
    cst[0][ys][xs] = cst[1][ys][xs] = 0;
    
    while (!deq.empty()) {
      int x = deq.front().first.first;
      int y = deq.front().first.second;
      bool h = deq.front().second;
      int c = cst[h][y][x];
      deq.pop_front();

      if (ng[y][x]) continue;
      
      if (x == xt && y == yt) {
        printf("%d\n", c);
        goto done;
      }
      
      // horizontal move!
      for (int dx = -1; dx <= 1; dx += 2) {
        int tx = x + dx, ty = y, tc = c + (h ? 0 : 1);
        bool th = true;
        if (tx < 0 || xid_ub <= tx) continue;

        if (cst[th][ty][tx] == -1 || tc < cst[th][ty][tx]) {
          if (h) deq.push_front(mp(mp(tx, ty), th));
          else   deq.push_back (mp(mp(tx, ty), th));
          cst[th][ty][tx] = tc;
        }
      }

      // vertical move
      for (int dy = -1; dy <= 1; dy += 2) {
        int tx = x, ty = y + dy, tc = c + (h ? 1 : 0);
        bool th = false;
        if (ty < 0 || yid_ub <= ty) continue;

        if (cst[th][ty][tx] == -1 || tc < cst[th][ty][tx]) {
          if (h) deq.push_back (mp(mp(tx, ty), th));
          else   deq.push_front(mp(mp(tx, ty), th));
          cst[th][ty][tx] = tc;
        }        
      }
    }
    return 1;  // IMPOSSIBLE
    
  done:;
  }
  
  return 0;
}
