#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

typedef long long ll;


int main() {
  int T;
  cin >> T;
  rep (ca, T) {
    int M, I;
    cin >> M >> I;

    vector<string> fld(M);
    rep (y, M) cin >> fld[y];

    rep (i, I) {
      vector<string> nxt(M);
      nxt[0] = fld[0];
      for (int y = 1; y < M - 1; ++y) {
        nxt[y].resize(M);
        nxt[y][0] = fld[y][0];
        for (int x = 1; x < M - 1; ++x) {
          int b = 0;
          for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
              if (fld[y + dy][x + dx] == 'b') ++b;
            }
          }
          if (b >= 5) nxt[y][x] = 'b';
          else nxt[y][x] = 'w';
        }
        nxt[y][M - 1] = fld[y][M - 1];
      }
      nxt[M - 1] = fld[M - 1];

      fld = nxt;
    }

    // rep (y, M) cout << fld[y] << endl;
    int b = 0;
    rep (y, M) rep (x, M) if (fld[y][x] == 'b') ++b;
    printf("%d %d\n", b, M * M - b);
  }

  return 0;
}
