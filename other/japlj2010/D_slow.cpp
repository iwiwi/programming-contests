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

int fld[1010][1010];

int main() {
  int N, W, H, D, F;
  scanf("%d%d%d%d%d", &N, &W, &H, &D, &F);
  {
    rep (y, H) rep (x, W) fld[y][x] = F;
    
    rep (i, N) {
      int A, B, X, Y;
      scanf("%d%d%d%d", &A, &B, &X, &Y);
      // printf("A=%d, B=%d\n", A, B);
      --A;
      --B;
      rep (y, D) rep (x, D) {
        char c;
        scanf(" %c", &c);
        if (c == '.') c = '0';
        int dec = c - '0';
        
        rep (t, Y) rep (s, X) {
          int tx = A + x + s * D;
          int ty = B + y + t * D;

          // printf("%d %d %d\n", ty, tx, fld[ty][tx]);
          fld[ty][tx] -= dec;
          //          printf("%d %d %d\n", ty, tx, fld[ty][tx]);
          
          if (fld[ty][tx] < 0) {
            goto ng;
          }
        }
      }
      continue;

    ng:
      printf("%d\n", i);
      goto done;
    }
    printf("%d\n", N);
  done:;
  }
  
  return 0;
}

