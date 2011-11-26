#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)

int M, N;
double A[20][20];

double prv1[1 << 16], prv2[16][1 << 16];
double nxt1[1 << 16], nxt2[16][1 << 16];

int main() {
  scanf("%d%d", &M, &N);
  rep (i, M) rep (j, N) scanf("%lf", &A[i][j]);

  rep (b, 1 << M) if (b) prv1[b] = 1.0;
  rep (i, M) rep (b, 1 << M) if (b && (b & (1 << i))) prv2[i][b] = 1.0;
  
  for (int r = N - 1; r >= 0; --r) {
    nxt1[0] = 0.0;
    rep (b, 1 << M) if (b) {
      rep (i, M) if (b & (1 << i)) {
        double p = A[i][r];
        nxt2[i][b] = p * prv2[i][b] + (1.0 - p) * nxt1[b - (1 << i)];
        // printf("%d %d %x: %f\n", r, i, b, nxt2[i][b]);
        // printf(" %f * %f + %f * %f\n", p, prv2[i][b], (1.0 - p), nxt1[b - (1 << i)]);
      }
      nxt1[b] = 0.0;
      rep (i, M) if (b & (1 << i)) {
        nxt1[b] = max(nxt1[b], nxt2[i][b]);
      }
    }
    memcpy(prv1, nxt1, sizeof(prv1));
    memcpy(prv2, nxt2, sizeof(prv2));
  }

  printf("%.15f\n", prv1[(1 << M) - 1]);
  return 0;
}
