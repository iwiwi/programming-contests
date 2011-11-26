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

int ans_sec = 987654321, ans_turn = 100;

vector<int> click_x, click_y;

void saiki(int sec, int turn, int fld[5][5]) {
  // if (sec > ans_sec) return;

//   rep (y, H) { printf("%*s", turn, ""); rep (x, W) printf("%d ", fld[y][x]); puts(""); }
//   puts("");

  // Done ?
  {
//     rep (y, H) rep (x, W) if (fld[y][x] != 0) goto ng;
//     // printf("%d %d\n", sec, turn);
// //     rep (i, click_x.size()) printf(" %d %d\n", click_x[i], click_y[i]);
//     if (sec < ans_sec) {
//       ans_sec = sec;
//       ans_turn = turn;
//     }
//     else if (sec == ans_sec && turn < ans_turn) {
//       ans_turn = turn;
//     }
//     return;
  ng:;
  }
  
  if (turn >= 5) return;

  // Press
  {
    rep (y, H) rep (x, W) { // Click (x, y) !!
      click_x.pb(x);
      click_y.pb(y);
      
      int tmp_sec = sec;
      int tmp[5][5];
      rep (ty, H) rep (tx, W) tmp[ty][tx] = fld[ty][tx];

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
//         if (tmp_sec > ans_sec) goto dmp;
//         if (tmp_sec >= ans_sec && turn + 1 >= ans_turn) goto dmp;

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
//           if (tmp_sec < ans_sec) {
//             ans_sec = tmp_sec;
//             ans_turn = turn + 1;
//           }
//           else if (tmp_sec == ans_sec && turn + 1 < ans_turn) {
//             ans_turn = turn + 1;
//           }
          ans_turn = min(ans_turn, turn + 1);
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

  saiki(0, 0, fld);

  printf("%d %d\n", ans_sec, ans_turn);
  
  if (ans_turn > 5) puts("-1");
  else printf("%d\n", ans_turn);
  return 0;
}
