#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair

typedef long long ll;

int K, X[310], Y[310];
int N, M, D[110];
double P[110];

int d;
bool vis[310];

void search(int k) {
  if (vis[k]) return;
  if ((N - 1) - X[k] <= d || Y[k] <= d) throw 0;  // reach
  vis[k] = true;

  rep (i, K) {
    if (abs(X[i] - X[k]) + abs(Y[i] - Y[k]) <= d * 2) search(i);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &M);
    rep (i, M) scanf("%d%lf", &D[i], &P[i]);

    for (K = 0; ; ++K){
      scanf("%d", &X[K]);
      if (X[K] == -1) break;
      scanf("%d", &Y[K]);
    }

    double ans = 0.0;
    rep (m, M) {
      d = D[m];

      memset(vis, 0, sizeof(vis));
      try {
        rep (k, K) {
          if (X[k] <= d || (N - 1) - Y[k] <= d) search(k);
        }
      } catch (...) {
        continue;
      }

      ans += P[m];
    }

    printf("%.10f\n", ans);
  }

  return 0;
}
