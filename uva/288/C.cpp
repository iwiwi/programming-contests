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


const int INF = 987654321;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

char fld[110][110];

int main() {
  int T;
  scanf("%d", &T);

  rep (ca, T) {
    string S;
    cin >> S;
    int N = S.length();

    int ans = INF;
    for (int w = 2; w < N; ++w) {
      int h = N / w;
      if (w * h != N) continue;

      rep (y, h) rep (x, w) fld[y][x] = 0;

      int d = 0, x = 0, y = 0;
      rep (i, N) {
        fld[y][x] = S[i];
        if (i == N - 1) break;

        for (;; d = (d + 1) % 4) {
          int tx = x + dx[d], ty = y + dy[d];
          if (tx < 0 || w <= tx) continue;
          if (ty < 0 || h <= ty) continue;
          if (fld[ty][tx] != 0) continue;
          break;
        }
        x += dx[d];
        y += dy[d];
      }

      rep (x, w) {
        rep (y, h) if (fld[y][x] != fld[0][x]) goto dmp;
      }
      ans = min(ans, w + h);
   dmp:;
    }

    printf("Case %d: ", ca + 1);
    if (ans == INF) puts("-1");
    else printf("%d\n", ans);
  }

  return 0;
}

