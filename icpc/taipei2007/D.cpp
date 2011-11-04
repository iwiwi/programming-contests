#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair

typedef long long ll;

int N, X[1010], Y[1010];

pair<int, int> dirs[1010];
int dirs_n;

int main() {
  int T;
  cin >> T;
  rep (ca, T) {
    scanf("%d", &N);
    rep (i, N) scanf("%d%d", &X[i], &Y[i]);

    int best_c = 0, best_n = 0;
    rep (i, N) {
      int ver = 0;

      dirs_n = 0;
      rep (j, N) {
        int dx = X[j] - X[i], dy = Y[j] - Y[i];
        if (dx == 0) {
          if (dy >= 0) ++ver;
        } else if (dx > 0) {
          if (dy == 0) dx = 1;
          else {
            int g = __gcd(dx, abs(dy));
            dx /= g;
            dy /= g;
          }
          dirs[dirs_n++] = mp(dx, dy);
        }
      }

      // printf("%d %d: ver = %d\n", X[i], Y[i], ver);

      if (ver > best_c) { best_c = ver; best_n = 1; }
      else if (ver == best_c) ++best_n;

      sort(dirs, dirs + dirs_n);
      dirs[dirs_n++] = mp(-1, -1);  // sentinel

      pair<int, int> prv = mp(-1, -1);
      int cnt = 0;
      rep (i, dirs_n) {
        // printf(" %d %d\n", dirs[i].first, dirs[i].second);
        if (dirs[i] != prv) {
          int c = cnt + 1;
          // printf("  c=%d\n", c);
          if (c > best_c) { best_c = c; best_n = 1; }
          else if (c == best_c) ++best_n;

          cnt = 0;
        }
        ++cnt;
        prv = dirs[i];
      }
    }

    printf("%d %d\n", best_c, best_n);
  }

  return 0;
}
