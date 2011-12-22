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

int VA, VB, SA, SB, MA;

double win[10][110][110];
double sum[10][110][110];  // sum[k][a][b] := k, [0, a) * [0, b)

int main() {
  while (5 == scanf("%d%d%d%d%d", &VA, &VB, &SA, &SB, &MA)) {
    ++SA;
    ++SB;

    double lb = 0.0, ub = 1.0;
    rep (iter, 100) {
      double md = (lb + ub) / 2;

      memset(win, 0, sizeof(win));
      for (int ma = 0; ma <= MA; ++ma) {
        for (int va = 0; va <= VA; ++va) {
          for (int vb = 0; vb <= VB; ++vb) {
            sum[ma][va + 1][vb + 1] =
                sum[ma][va][vb + 1] + sum[ma][va + 1][vb] - sum[ma][va][vb];

            if (va == 0 && vb == 0) win[ma][va][vb] = md;
            else if (va == 0) win[ma][va][vb] = 0.0;
            else if (vb == 0) win[ma][va][vb] = 1.0;
            else {
              // Don't use
              {
                double w0 = 0;
                int saub = min(SA, vb);
                int sbub = min(SB, va);
                // [0, va) * [0, vb)
                // (va - sbub, va] * (vb - saub, vb]
                // = [va - sbub + 1, va + 1) * [vb - saub + 1, vb + 1)
                w0 += sum[ma][va + 1][vb + 1]
                    - sum[ma][va - sbub + 1][vb + 1]
                    - sum[ma][va + 1][vb - saub + 1]
                    + sum[ma][va - sbub + 1][vb - saub + 1];
                // [0, va) * [vb, SA)
                if (vb < SA) w0 += (SA - vb) * min(va, SB);
                // [va, SB) * [vb, SA)
                if ( va < SB && vb < SA) w0 += md * (SA - vb)  * (SB - va);

                w0 /= SA * SB - 1;
                win[ma][va][vb] = w0;
              }

              // Use
              if (ma > 0) {
                int tva = va / 2 + va % 2;
                int tvb = vb / 2 + vb % 2;
                win[ma][va][vb] = max(win[ma][va][vb], win[ma - 1][tva][tvb]);
              }
            }

            sum[ma][va + 1][vb + 1] += win[ma][va][vb];
          }
        }
      }

      double res = win[MA][VA][VB];
      if (res < md) ub = md;
      else lb = md;
    }
    printf("%.10f\n", (lb + ub) / 2.0);
  }
  return 0;
}

