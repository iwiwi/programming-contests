#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back

const int W = 4;
const int H = 4;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int ans_sec = 987654321, ans_turn = 6;

vector<int> click_x, click_y;

void saiki(int sec, int turn, int fld[5][5]) {
  if (turn >= ans_turn) return;

  // Prune
  {
    int ma = 0;
    rep (y, 4) rep (x, 4) {
      ma = max(ma, fld[y][x]);
    }
    if (turn + (5 - ma) - 1 >= ans_turn) return;
  }
  
  {
    // Press
    rep (y, H) rep (x, W) { // Click (x, y) !!
      click_x.pb(x);
      click_y.pb(y);
      
      int tmp_sec = sec;
      int tmp[5][5];
      rep (ty, H) rep (tx, W) tmp[ty][tx] = fld[ty][tx];

      if (turn + (5 - tmp[y][x]) - 1 >= ans_turn) continue;

      vector<int> px, py, pd;
      if (++tmp[y][x] >= 5) { // Simulate!!
        tmp[y][x] = 0;
        rep (d, 4) {
          px.pb(x + dx[d]);
          py.pb(y + dy[d]);
          pd.pb(d);
        }
      }

      int crr_bubble = 0;
      rep (ty, H) rep (tx, W) if (tmp[ty][tx] > 0) ++crr_bubble;
      
      while (!px.empty()) {
        ++tmp_sec;

        vector<int> qx, qy, qd;
        rep (i, px.size()) {
          int xx = px[i], yy = py[i], dd = pd[i];
          if (xx < 0 || W <= xx || yy < 0 || H <= yy) continue;
          if (tmp[yy][xx] > 0) ++tmp[yy][xx];
          else {
            qx.pb(xx + dx[dd]);
            qy.pb(yy + dy[dd]);
            qd.pb(dd);
          }
        }
        
        // Bomb!!
        rep (i, px.size()) {
          int xx = px[i], yy = py[i];
          if (xx < 0 || W <= xx || yy < 0 || H <= yy) continue;
          if (tmp[yy][xx] >= 5) {
            tmp[yy][xx] = 0;
            --crr_bubble;
            rep (d, 4) {
              qx.pb(xx + dx[d]);
              qy.pb(yy + dy[d]);
              qd.pb(d);
            }
          }
        }


        if (crr_bubble == 0) {
          ans_turn = min(ans_turn, turn);
          goto dmp;
        }
        
        px.swap(qx);
        py.swap(qy);
        pd.swap(qd);
      }

      saiki(tmp_sec, turn + 1, tmp);
    dmp:;
      click_x.pop_back();
      click_y.pop_back();
    }
  }
}

int main() {
  int fld[5][5];
  rep (y, H) rep (x, W) scanf("%d", &fld[y][x]);

  {
    rep (y, H) rep (x, W) if (fld[y][x] != 0) goto nonzero;
    puts("0");
    return 0;
  nonzero:;
  }

  ans_turn = 6;
  saiki(0, 1, fld);
  // printf("%d %d\n", ans_sec, ans_turn);
  if (ans_turn > 5) puts("-1");
  else printf("%d\n", ans_turn);
  return 0;
}
