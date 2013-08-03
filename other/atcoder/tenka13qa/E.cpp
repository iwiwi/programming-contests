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

const char *pieces[] = {
  ".   #   .   #   .   #   .   #   .   #   .   #   .   #   .   # ",
  "..  ..  #.  #.  .#  .#  ##  ##  ..  ..  #.  #.  .#  .#  ##  ##",
  ".   .   .   .   .   .   .   .   #   #   #   #   #   #   #   # ",
};
char P[16][4];

const int dx[][4] = {{0, 0, 1, 0}, {2, 1, 1, 0}, {0, 0, -1, 0}, {-1, 0, 0, 1}};
const int dy[][4] = {{0, 1, 1, 2}, {0, 0, 1, 0}, {2, 1,  1, 0}, { 1, 1, 0, 1}};

int W, H, N;
char F[20][20];
int T[100];

int cov[20][20];
bool usd[100];

int ans[100][3];

void search(int x, int y) {
  if (y == H + 1) throw "yeah";
  else if (x == W + 1) search(1, y + 1);
  else if (cov[y][x]) search(x + 1, y);
  else {
    int msk = 0;
    rep (i, N) if (!usd[i]) {
      int t = T[i];
      if (msk & (1 << t)) continue;
      msk |= 1 << t;
      usd[i] = true;

      rep (d, 4) {
        rep (j, 4) {
          int tx = x + dx[d][j], ty = y + dy[d][j];
          if (cov[ty][tx] || F[ty][tx] != P[t][j]) goto dmp;
        }
        rep (j, 4) {
          int tx = x + dx[d][j], ty = y + dy[d][j];
          cov[ty][tx] = t + 1;
        }
        ans[i][0] = x + dx[d][0];
        ans[i][1] = y + dy[d][0];
        ans[i][2] = d;
        search(x + 1, y);
        rep (j, 4) {
          int tx = x + dx[d][j], ty = y + dy[d][j];
          cov[ty][tx] = 0;
        }
     dmp:;
      }

      usd[i] = false;
    }
  }
}

int main() {
  rep (i, 16) {
    P[i][0] = pieces[0][i * 4];
    P[i][1] = pieces[1][i * 4];
    P[i][2] = pieces[1][i * 4 + 1];
    P[i][3] = pieces[2][i * 4];
  }

  while (2 == scanf("%d%d", &H, &W)) {
    memset(F, '*', sizeof(F));
    for (int y = 1; y <= H; ++y) for (int x = 1; x <= W; ++x) scanf(" %c", &F[y][x]);

    scanf("%d", &N);
    rep (i, N) {
      scanf("%d", &T[i]);
      --T[i];
    }

    try {
      memset(cov, 0, sizeof(cov));
      memset(usd, 0, sizeof(usd));
      search(1, 1);
    } catch (...) {
      rep (i, N) printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
      continue;
    }
    puts("-1");
  }

  return 0;
}

