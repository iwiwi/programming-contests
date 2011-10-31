#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define pb push_back

int N, E, T, W[310];
int G[1010], C[1010], S[1010][20];

int score[310];

int main() {
  while (3 == scanf("%d%d%d", &N, &E, &T)) {
    --T;
    rep (i, N) scanf("%d", &W[i]);
    rep (i, E) {
      scanf("%d%d", &G[i], &C[i]);
      --G[i];
      rep (j, C[i]) {
        scanf("%d", &S[i][j]);
        --S[i][j];
      }
    }

    rep (i, N) {
      if (W[i] == 1) score[i] = 1;
      else score[i] = -1;
    }

    rep (iter, N) {
      int best_s = INT_MAX, best_g = -1;

      rep (i, E) {
        if (score[G[i]] != -1) continue;

        vector<int> tmp;
        rep (j, C[i]) {
          if (score[S[i][j]] == -1) goto dmp;
          tmp.pb(score[S[i][j]]);
        }
        sort(tmp.begin(), tmp.end());

        {
          int s = C[i];
          rep (j, tmp.size()) s = max(s, C[i] - 1 - j + tmp[j]);
          if (s < best_s) {
            best_s = s;
            best_g = G[i];
          }
        }
     dmp:;
      }

      // printf(" %d %d\n", best_g, best_s);

      if (best_g == -1) break;
      score[best_g] = best_s;
    }

    printf("%d\n", score[T]);
  }

  return 0;
}
