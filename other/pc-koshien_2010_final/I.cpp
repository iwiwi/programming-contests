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

const int INF = 1E9;
const int dx[3] = {1, -1, 0};
const int dy[3] = {0, 0, 1};

int W, H;
int F, M, oxy;
int fld[20][20];

typedef pair<int, pair<pair<int, int>, pair<int, int> > > s_t;

int main() {
  for (;;) {
    scanf("%d%d", &W, &H);
    if (W == 0 && H == 0) return 0;
    scanf("%d%d%d", &F, &M, &oxy);
    rep (y, H) rep (x, W) scanf("%d", &fld[y][x]);

    multimap<int, s_t> que;
    map<s_t, int> pot;

    rep (x, W) {
      s_t s = mp(oxy, mp(mp(x, 0), mp(x, x)));
      que.insert(mp(0, s));
      pot[s] = 0;
    }

    int ans = INF;
    while (!que.empty()) {
      int c = que.begin()->first;
      s_t s = que.begin()->second;
      int o = s.first;
      int x = s.second.first.first;
      int y = s.second.first.second;
      int l = s.second.second.first;
      int r = s.second.second.second;
      que.erase(que.begin());
      if (c > pot[s]) continue;
      if (c > F) break;

      --o;
      if (o <= 0) continue;  // DIE

      if (x < l || r <= x) {
        if (fld[y][x] > 0) o = min(M, o + fld[y][x]);
        else c += -fld[y][x];
        l = min(l, x);
        r = max(r, x + 1);
      }

      if (y == H - 1) {
        ans = min(ans, c);
        continue;
      }

      // printf("%d, %d, %d-%d-%d --- %d\n", o, y, l, x, r, c);

      rep (i, 3) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (tx < 0 || W <= tx) continue;;
        int tl = l, tr = r;
        if (ty > y) tl = tr = tx;
        s_t ts = mp(o, mp(mp(tx, ty), mp(tl, tr)));

        if (pot.count(ts) && c >= pot[ts]) continue;

        que.insert(mp(c, ts));
        pot[ts] = c;
      }
    }

    if (ans > F) puts("NA");
    else printf("%d\n", ans);
  }

  return 0;
}

