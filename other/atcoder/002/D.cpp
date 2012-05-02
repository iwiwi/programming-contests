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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int H, W;
char fld[2010][2010];

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) scanf("%s", fld[y]);

    int od = INT_MAX, xd = INT_MAX;
    rep (y, H) {
      for (int x = 0; x < W; ++x) {
        if (fld[y][x] == 'o') break;
        if (fld[y][x] == 'x') xd = min(xd, x);
      }
      for (int x = W - 1; x >= 0; --x) {
        if (fld[y][x] == 'x') break;
        if (fld[y][x] == 'o') od = min(od, (W - 1) - x);
      }
    }

    if (od != INT_MAX && xd != INT_MAX) {
      if (od <= xd) puts("o");
      else puts("x");
      continue;
    }

    // ((weight, count), (o, x))
    vector<pair<pair<int, int>, pair<int, int> > > blocks;
    int o_free = 0, x_free = 0;

    rep (y, H) {
      int x = 0;
      for (;;) {
        while (x < W && fld[y][x] != 'o') ++x;
        if (x == W) break;

        string os, xs;

        while (x < W && fld[y][x] != 'x') os += fld[y][x++];
        if (x == W) break;

        while (x < W && fld[y][x] != 'o') xs += fld[y][x++];

        int center = 0;
        while (os[os.length() - 1 - center] == '.') ++center;
        os = os.substr(0, os.length() - center);
        reverse(all(os));

        assert(os[0] == 'o');
        assert(xs[0] == 'x');

        int of = 0, xf = 0, t;
        t = 0; rep (i, os.length()) { if (os[i] == 'o') of += t; else ++t; }
        t = 0; rep (i, xs.length()) { if (xs[i] == 'x') xf += t; else ++t; }
        int oc = count(all(os), 'o');
        int xc = count(all(xs), 'x');
        blocks.pb(mp(mp(oc + xc, center), mp(oc, xc)));

        // cout << os << ":" << string(center, '.') << ":" << xs << endl;
        // printf(" o:%d, x:%d\n", of, xf);

        o_free += of;
        x_free += xf;
      }
    }

    sort(all(blocks));
    reverse(all(blocks));

    bool turn_o = true;
    rep (i, blocks.size()) {
      int center = blocks[i].first.second;
      int oc = blocks[i].second.first;
      int xc = blocks[i].second.second;

      // printf("%d: %d %d\n", center, oc, xc);
      for (; center > 1; --center) {
        if (turn_o) o_free += oc - 1;
        else        x_free += xc - 1;
        turn_o = !turn_o;
      }
    }

    // printf("%d vs %d, start : %c\n", o_free, x_free, turn_o ? 'o' : 'x');

    bool o_lose;
    if (turn_o) o_lose = o_free <= x_free;
    else        o_lose = o_free <  x_free;

    if (o_lose) puts("x");
    else puts("o");
  }


  return 0;
}

