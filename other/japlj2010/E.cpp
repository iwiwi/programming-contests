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
using namespace std;
 
#define all(c) (c).begin(), (c).end() 
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int W, H, M, S, T;
int X1[510], Y1[510], X2[510], Y2[510], A[510], B[510];

int fld[110][110];


int stki[1000010], stkh[1000010];

int largest_rectangle(const vector<int> &a) {
  // a.push_back(0);
  assert(a.back() == 0);  // a sentinel must be added
  
  int stkp = 0, res = 0;
  rep (i, a.size()) {
    int j = i;
    while (stkp > 0 && stkh[stkp - 1] >= a[i]) {
      j = stki[stkp - 1];
      res = max(res, stkh[stkp - 1] * (i - j));
      --stkp;
    }
    stki[stkp] = j;
    stkh[stkp] = a[i];
    ++stkp;
  }
  return res;
}

// fld: obstacle <=> true
int largest_rectangle(const vector<vector<bool> > &fld) {
  int H = fld.size(), W = fld[0].size();
  int res = 0;
  vector<int> up(W + 1);
  rep (y, H) {
    rep (x, W) up[x] = fld[y][x] ? 0 : up[x] + 1;
    res = max(res, largest_rectangle(up));
  }
  return res;
}


int main() {
  while (5 == scanf("%d%d%d%d%d", &W, &H, &M, &S, &T)) {
    rep (i, M) {
      scanf("%d%d%d%d%d%d", X1+i, Y1+i, X2+i, Y2+i, A+i, B+i);
    }

    int lb = 0, ub = T + 1;
    while (ub - lb > 1) {
      int req = lb + (ub - lb) / 2;
    //   printf("%d-%d (%d)\n", lb, ub, req);
    //for (int req = 0; req <= T; ++req) {
      vector<pair<int, int> > evt;
      rep (i, M) {
        evt.pb(mp(A[i] - req + 1, i * 2 + 0));
        evt.pb(mp(B[i], i * 2 + 1));
      }
      evt.pb(mp(0, -1));
      sort(all(evt));      
      
      memset(fld, 0, sizeof(fld));
      int i = 0, ma = 0;
      vector<vector<bool> > fldb(H, vector<bool>(W));
      while (i < (int)evt.size()) {
        int t = evt[i].first;
        while (i < (int)evt.size() && evt[i].first == t) {
          if (evt[i].second < 0) {
            ++i;
            continue;
          }
          int k = evt[i].second / 2;
          int d = evt[i].second % 2 == 0 ? 1 : -1;
          ++i;
          for (int x = X1[k]; x < X2[k]; ++x) {
            for (int y = Y1[k]; y < Y2[k]; ++y) {
              fld[y][x] += d;
            }
          }
        }

        if (t < 0 || t + req > T) continue;

        // printf("\nt=%d\n", t);
        // rep (y, H) { rep (x, W) printf("%c", fld[y][x] ? '#' : ' '); puts(""); }

        // rep (y, H) rep (x, W) {
        //   for (int w = 1; x + w <= W; ++w) {
        //     for (int h = 1; y + h <= H; ++h) {
        //       rep (dx, w) rep (dy, h) {
        //         if (fld[y + dy][x + dx]) goto dmp;
        //       }
        //       ma = max(ma, w * h);
        //     dmp:;
        //     }
        //   }
        // }
        
        // int up[110], stkx[110], stku[110], stk_h;
        // memset(up, 0, sizeof(up));
        // rep (y, H) {
        //   stk_h = 0;
        //   rep (x, W) {
        //     up[x] = fld[y][x] ? 0 : up[x] + 1;
        //     int tx = x;
            
        //     while (stk_h > 0 && stku[stk_h - 1] >= up[x]) {
        //       tx = stkx[stk_h - 1];
        //       ma = max(ma, (x - tx) * stku[stk_h - 1]);
        //       --stk_h;
        //     }
        //     stkx[stk_h] = tx;
        //     stku[stk_h] = up[x];
        //     ++stk_h;
        //   }
        //   while (stk_h > 0) {
        //     ma = max(ma, (W - stkx[stk_h - 1]) * stku[stk_h - 1]);
        //     --stk_h;
        //   }
        // }

        rep (y, H) rep (x, W) fldb[y][x] = !!fld[y][x];
        ma = max(ma, largest_rectangle(fldb));
        if (ma >= S) break;
      }

      // printf("req=%d, ma=%d\n", req, ma);
      if (ma >= S) lb = req;
      else ub = req;
    }
    printf("%d\n", lb);
  }
  
  return 0;
}

