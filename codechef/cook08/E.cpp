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

int W, H, x, y, L;
char S[4000010];

int fld[1010][1010];

void mov(char c, int &x, int &y) {
  switch (c) {
    case 'U': ++y; break;
    case 'D': --y; break;
    case 'L': --x; break;
    case 'R': ++x; break;
  }
}

int main() {
  int cases;
  scanf("%d", &cases);
  rep (ca, cases) {
    scanf("%d%d%d%d%d", &W, &H, &x, &y, &L);
    --x;
    --y;
    scanf("%s", S);

    memset(fld, -1, sizeof(fld));
    fld[y][x] = 0;
    rep (i, L - 1) {
      mov(S[i], x, y);
      fld[y][x] = i + 1;
    }

    char c = S[L - 2];
    for (int i = L; ; ++i) {
      mov(c, x, y);
      if (x < 0 || W <= x || y < 0 || H <= y) {
        printf("WALL %d\n", i - L);
        break;
      }
      if (fld[y][x] != -1 && i - fld[y][x] < L) {
        printf("BODY %d\n", i - L);
        break;
      }
    }
  }

  return 0;
}

