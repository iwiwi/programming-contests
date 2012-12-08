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

vector<string> rotate(const vector<string> &f) {
  int h = f.size(), w = f[0].length();
  vector<string> r(w, string(h, ' '));
  rep (y, h) rep (x, w) r[x][h - y - 1] = f[y][x];
  return r;
}

vector<string> flip(const vector<string> &f) {
  vector<string> r = f;
  rep (y, r.size()) reverse(all(r[y]));
  return r;
}

int solve(const vector<string> &f) {
  int h = f.size(), w = f[0].length();

  int res = 0;
  rep (y, h) rep (x, w) {
    int t = 0;
    for (int s = 1; y + s <= h && x + s <= w; ++s) {
      rep (i, s) {
        char c = f[y + s - 1][x + i];
        if (c == 'X') goto ng;
        t += c - '0';
      }
      res = max(res, t);
    }
 ng:;
  }

  return res;
}

int main() {
  int h, w;
  while (cin >> h >> w) {
    vector<string> fld(h);
    rep (y, h) cin >> fld[y];

    int ans = 0;
    rep (d1, 2) {
      rep (d2, 4) {
        ans = max(ans, solve(fld));
        fld = rotate(fld);
      }
      fld = flip(fld);
    }

    printf("%d\n", ans);
  }

  return 0;
}

