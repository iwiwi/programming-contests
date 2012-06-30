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

const int N = 9;

int X, Y;
char fld[20][20];

int main() {
  char w[10];
  while (3 == scanf("%d%d%s", &X, &Y, w)) {
    --X; --Y;

    int dx = 0, dy = 0;
    if (strchr(w, 'R')) dx = +1;
    if (strchr(w, 'L')) dx = -1;
    if (strchr(w, 'U')) dy = -1;
    if (strchr(w, 'D')) dy = +1;

    rep (y, N) scanf("%s", fld[y]);

    string ans = "";
    int x = X, y = Y;
    rep (i, 4) {
      ans += fld[y][x];

      int tx = x + dx, ty = y + dy;
      if (tx < 0 || N <= tx) { dx *= -1; tx = x + dx; }
      if (ty < 0 || N <= ty) { dy *= -1; ty = y + dy; }
      x = tx;
      y = ty;
    }

    cout << ans << endl;
  }

  return 0;
}

