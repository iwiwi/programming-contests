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
#include <tr1/unordered_map>
#include <tr1/unordered_set>
using namespace std;
using namespace std::tr1;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

#define F first
#define S second


typedef unsigned long long ull;
const int INF = 1 << 29;

int H, W;
char fld[20][20];
bool end[20][20];
unordered_map<ull, int> mem;

ull memcount = 0;

ull myhash(int x, int y, const vector<int> &b) {
  const ull B = 100000007;
  ull e = 0;
  rep (i, b.size()) e = e * B + b[i];
  e = e * B + (x * H + y);
  return e;
}

int search(int x, int y, const vector<int> &b) {
  if (x == W) return search(0, y + 1, b);
  if (y == H) return b.size() <= 1 ? 0 : INF;

  if (!b.empty() && b[0] == 0) return INF;

  ull e = myhash(x, y, b);
  if (mem.count(e)) return mem[e];
  int res = INF;

  int all1 = (1 << W) - 1;
  int all2 = (1 << (W + 1)) - 1;
  int flg = 1 << W;

  // Place
  if (fld[y][x] != '#') {
    int me = (1 << x) | ((fld[y][x] == 'H') << W);
    int le = 0, up = 0;
    vector<int> tb;
    rep (i, b.size()) {
      int s = b[i];
      if ((s | (s << 1)) & (1 << x)) {
        if ((s << 0) & (1 << x)) up = s;
        if ((s << 1) & (1 << x)) le = s;
      }
      else tb.pb(s);
    }

    bool meH = fld[y][x] == 'H';
    bool leH = x > 0 && fld[y][x - 1] == 'H';
    bool upH = y > 0 && fld[y - 1][x] == 'H';

    if (meH) {
      if (!leH && le) {
        tb.pb((me | le) & all1);
        if (up && up != le) tb.pb(up & (all2 - (1 << x)));
      } else if (!upH && up) {
        tb.pb((me | up) & all1);
        if (le && le != up) tb.pb(le & (all2 - (1 << x)));
      } else {
        tb.pb(me);
        if (le) tb.pb(le & (all2 - (1 << x)));
        if (up) tb.pb(up & (all2 - (1 << x)));
      }
    } else {
      if (!leH || (le & flg)) { me |= le; le = 0; }
      if (!upH || (up & flg)) { me |= up; up = 0; }
      tb.pb(me & all1);
      if (up            ) tb.pb(up & (all2 - (1 << x)));
      if (le && le != up) tb.pb(le & (all2 - (1 << x)));
    }

    sort(all(tb));
    tb.erase(unique(all(tb)), tb.end());
    res = min(res, 1 + search(x + 1, y, tb));
  }

  // Don't place
  if (fld[y][x] != 'H') {
    if (end[y][x] && b.size() == 1) res = min(res, 0);
    else {
      vector<int> tb(b);
      rep (i, tb.size()) {
        int s = tb[i];
        if (s == 1 << x) goto ng;
        else if (s & (1 << x)) tb[i] = s ^ (1 << x);
      }
      sort(all(tb));
      res = min(res, search(x + 1, y, tb));
   ng:;
    }
  }

  if (mem.size() < 2000000) mem[e] = res;
  return res;
}

void revY() {
  for (int y1 = 0, y2 = H - 1; y1 < y2; ++y1, --y2) {
    rep (x, W) swap(fld[y1][x], fld[y2][x]);
  }
}

void revX() {
  rep (y, H) reverse(fld[y], fld[y] + W);
}

int solve() {
  mem.clear();
  bool ok = true;
  for (int y = H - 1; y >= 0; --y) {
    for (int x = W - 1; x >= 0; --x) {
      ok = end[y][x] = ok && fld[y][x] != 'H';
    }
  }

  int ans = -search(0, 0, vector<int>());
  rep (y, H) rep (x, W) ans += fld[y][x] == '#' ? 0 : 1;
  return max(-1, ans);
}

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    int ans = -1;
    rep (y, H) scanf("%s", fld[y]);

    ans = max(ans, solve());
    revY();
    ans = max(ans, solve());
    revX();
    ans = max(ans, solve());
    revY();
    ans = max(ans, solve());

    printf("%d\n", ans);
  }

  return 0;
}
