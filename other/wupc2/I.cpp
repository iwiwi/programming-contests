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

typedef long long ll;

const int W = 2000, H = 2000;
const int P = W / 2;

int yoko[H + 10][W + 10], tate[H + 10][W + 10], nana[H + 10][W + 10];

inline int f(int T, int S, int s) {
  if (T == 1) return 1;
  else if (T == 2) return S - s + 1;
  else return (S - s + 1) * (S - s + 1);
}

int main() {
  int N;
  while (1 == scanf("%d", &N) && N) {
    memset(yoko, 0, sizeof(yoko));
    memset(tate, 0, sizeof(tate));
    memset(nana, 0, sizeof(nana));

    rep (i, N) {
      int T, X, Y, S;
      scanf("%d%d%d%d", &T, &X, &Y, &S);
      --S;
      X += P;
      Y += P;

      yoko[Y][X] += f(T, S, 0);
      yoko[Y][X + 1] -= f(T, S, 0);

      for (int s = 1; s <= S; ++s) {
        int v = f(T, S, s);

        yoko[Y + s][X - s] += v;
        yoko[Y + s][X] -= v;

        yoko[Y - s][X + s + 1] -= v;
        yoko[Y - s][X + 1] += v;

        tate[Y][X - s] += v;
        tate[Y + s][X - s] -= v;

        tate[Y + 1][X + s] -= v;
        tate[Y - s + 1][X + s] += v;

        nana[Y - s][X] += v;
        nana[Y][X - s] -= v;

        nana[Y + s + 1][X - 1] -= v;
        nana[Y + 1][X + s - 1] += v;
      }
    }

    // for (int y = H - 1; y >= 0; --y) {
    //   rep (x, W) printf("%3d", yoko[y][x]);
    //   puts("");
    // }
    // puts("");

    rep (y, H) for (int x = 1; x < W; ++x) yoko[y][x] += yoko[y][x - 1];
    rep (x, W) for (int y = 1; y < H; ++y) tate[y][x] += tate[y - 1][x];
    for (int y = 1; y < H; ++y) for (int x = 0; x + 1 < W; ++x) nana[y][x] += nana[y - 1][x + 1];

    int ans = 0;
    rep (y, H) rep (x, W) {
      ans = max(ans,yoko[y][x] + tate[y][x] + nana[y][x]);
    }
    printf("%d\n", ans);

    // for (int y = H - 1; y >= 0; --y) { rep (x, W) printf("%3d", yoko[y][x] + tate[y][x] + nana[y][x]); puts(""); } puts("CHANGE W AND H!!");
  }

  return 0;
}

