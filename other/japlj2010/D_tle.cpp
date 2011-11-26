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

int N, /*W, H, */ D, F;
int A[100010], B[100010], X[100010], Y[100010];
int P[100010][10][10];

int fldW, fldH;
int fld[1010][1010];
int dif[1010][1010];

int lef[100010];
int top[100010];
int pat[100010];

bool doit(int from, int to) {
  int inc = -1;
  if (from > to) {
    swap(from, to);
    inc *= -1;
  }

  rep (y, fldH) rep (x, fldW) dif[y][x] = 0;
  for (int i = from; i < to; ++i) {
    int x = lef[i], y = top[i], w = X[i], h = Y[i];
    int p = inc * pat[i];
    dif[y    ][x    ] += p;
    dif[y    ][x + w] -= p;
    dif[y + h][x    ] -= p;
    dif[y + h][x + w] += p;
  }

  bool ok = true;
  rep (x, fldW) {
    ok &= 0 <= (fld[0][x] += dif[0][x]);
    dif[0][x + 1] += dif[0][x];
  }

  for (int y = 1; y < fldH; ++y) {
    dif[y][0] += dif[y - 1][0];
    ok &= 0 <= (fld[y][0] += dif[y][0]);
    
    for (int x = 1; x < fldW; ++x) {
      dif[y][x] += dif[y][x - 1] + dif[y - 1][x] - dif[y - 1][x - 1];
      ok &= 0 <= (fld[y][x] += dif[y][x]);
    }
  }
  return ok;

  // rep (y, fldH) rep (x, fldW) dif[y][x + 1] += dif[y][x];
  // rep (x, fldW) rep (y, fldH) dif[y + 1][x] += dif[y][x];
  // rep (y, fldH) rep (x, fldW) fld[y][x] += dif[y][x];

  //  rep (y, fldH) rep (x, fldW) if (fld[y][x] < 0) return false;
  // return true;
}

int readint() {
  int c;
  for (c = getchar(); !isdigit(c); c = getchar());

  int d = c - '0';
  for (c = getchar(); isdigit(c); c = getchar()) d = d * 10 + (c - '0');
  return d;
}

int main() {
  int W, H;
  while (5 == scanf("%d%d%d%d%d", &N, &W, &H, &D, &F)) {
    char buf[256];
      
    rep (i, N) {
      // scanf("%d%d%d%d", A + i, B + i, X + i, Y + i);
      // --A[i];
      // --B[i];
      
      A[i] = readint() - 1;
      B[i] = readint() - 1;
      X[i] = readint();
      Y[i] = readint();
      // printf(" %d %d %d %d\n", A[i], B[i], X[i], Y[i]);
      
      // rep (y, D) rep (x, D) {
      //   char c;
      //   scanf(" %c", &c);
      //   P[i][y][x] = c == '.' ? 0 : c - '0';
      // }

      rep (y, D) {
        scanf("%s", buf);
        // printf("|%s|\n", buf);
        rep (x, D) {
          char c = buf[x];
          P[i][y][x] = c == '.' ? 0 : c - '0';
        }
      }
    }

    
    vector<int> dxs, dys;
    rep (dx, D) rep (dy, D) {
      dxs.pb(dx);
      dys.pb(dy);
    }
    vector<int> ord(D * D);
    rep (i, ord.size()) ord[i] = i;
    random_shuffle(all(ord));

    int ans = N;    
    rep (i, ord.size()) {
      int dx = dxs[ord[i]];
      int dy = dys[ord[i]];
      
      fldW = (W - dx) / D + !!((W - dx) % D);
      fldH = (H - dy) / D + !!((H - dy) % D);
      rep (y, fldH) rep (x, fldW) fld[y][x] = F;

      rep (i, ans) {
        lef[i] = (dx >= A[i] % D ? A[i] / D : A[i] / D + 1);
        top[i] = (dy >= B[i] % D ? B[i] / D : B[i] / D + 1);
        pat[i] = P[i][((dy - B[i]) % D + D) % D][((dx - A[i]) % D + D) % D];
      }

      int crr = 0;
      if (doit(crr, ans)) continue;
      crr = ans;
      
      // printf("### dx=%d, dy=%d : %d x %d\n", dx, dy, fldW, fldH);

      int lb = 0, ub = ans + 1;
      while (ub - lb > 1) {
        int nxt = (lb + ub) / 2;
        //printf("# %d-%d: %d\n", lb, ub, nxt);
        if (doit(crr, nxt)) lb = nxt;
        else ub = nxt;
        crr = nxt;
      }
      ans = lb;
    }

    printf("%d\n", ans);
  }
  
  return 0;
}

