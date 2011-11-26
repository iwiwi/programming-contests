#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

int N;
int X1[510], Y1[510], X2[510], Y2[510];

int cnt;
int ans[510];
bool done[510];

void saiki(int x1, int y1, int x2, int y2) {
  for (;;) {
    pair<pair<int, int>, int> s = mp(mp(510, 510), -1);
    rep (i, N) {
      if (done[i]) continue;
      if (x1 <= X1[i] && X2[i] <= x2 && y1 <= Y1[i] && Y2[i] <= y2) {
        s = min(s, mp(mp(X1[i], Y1[i]), i));
      }
    }
    // printf("%d %d %d %d -> %d\n", x1, y1, x2, y2, s.second);
    if (s.second == -1) return;

    int k = s.second;
    ans[k] = ++cnt;
    done[k] = true;

    int l = X1[k], y = Y2[k];
    int r = x2;
    rep (i, N) {
      if (done[i]) continue;
      if (x1 <= X1[i] && X2[i] <= x2 && y1 <= Y1[i] && Y2[i] <= y2) {
        if (X1[i] >= l && Y1[i] < y && y < Y2[i]) {
          r = min(r, X1[i]);
        }
      }
    }

    saiki(l, 0, r, y);
  }
}

int main() {
  bool f = true;
  while (scanf("%d", &N) == 1 && N) {
    rep (i, N) {
      scanf("%d%d%d%d", X1 + i, Y1 + i, X2 + i, Y2 + i);
      if (X1[i] > X2[i]) swap(X1[i], X2[i]);
      if (Y1[i] > Y2[i]) swap(Y1[i], Y2[i]);
    }

    memset(done, 0, sizeof(done));
    cnt = 0;
    saiki(0, 0, 510, 510);

    if (!f) puts("");
    else f = false;
    rep (i, N) printf("%d\n", ans[i]);
  }
}
