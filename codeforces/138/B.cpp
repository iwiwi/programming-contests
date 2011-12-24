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

int main() {
  string s;
  while (cin >> s) {
    int a[10] = {}, b[10] = {};
    rep (d, 10) a[d] = b[d] = count(all(s), '0' + d);

    int best_s = -1, best_l = 0;
    for (int s = 1; s <= 9; ++s) {
      int t = 10 - s;
      --a[s];
      --b[t];

      if (a[s] >= 0 && b[t] >= 0) {
        int l = 1, t[10] = {};
        rep (d, 10) {
          l += (t[d] = min(a[d], b[9 - d]));
          a[d]     -= t[d];
          b[9 - d] -= t[d];
        }
        l += min(a[0], b[0]);

        if (l > best_l) {
          best_s = s;
          best_l = l;
        }

        rep (d, 10) {
          a[d]     += t[d];
          b[9 - d] += t[d];
        }
      }

      ++a[s];
      ++b[t];
    }

    string p, q;

    if (best_s != -1) {
      p += '0' + best_s;        --a[best_s];
      q += '0' + (10 - best_s); --b[10 - best_s];

      rep (d, 10) {
        while (a[d] > 0 && b[9 - d] > 0) {
          p += '0' + d;       --a[d];
          q += '0' + (9 - d); --b[9 - d];
        }
      }
    }

    int z = min(a[0], b[0]);
    p = string(z, '0') + p; a[0] -= z;
    q = string(z, '0') + q; b[0] -= z;
    for (int d = 0; d <= 9; ++d) {
      p += string(a[d], '0' + d);
      q += string(b[d], '0' + d);
    }

    reverse(all(p));
    reverse(all(q));
    cout << p << endl
         << q << endl;
  }

  return 0;
}

