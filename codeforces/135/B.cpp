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

int X[8], Y[8];

bool is_rectangle(int b) {
  rep (i, 8) if (b & (1 << i)) {
    rep (j, 8) if ((b & (1 << j)) && i != j) {
      rep (k, j) if ((b & (1 << k)) && i != k) {
        if ((X[j] - X[i]) * (X[k] - X[i]) + (Y[j] - Y[i]) * (Y[k] - Y[i]) == 0) goto ok;
      }
    }
    return false;
 ok:;
  }
  return true;
}

int sqr(int x) { return x * x; }

bool is_square(int b) {
  vector<int> d;
  rep (i, 8) if (b & 1 << i) {
    rep (j, i) if (b & 1 << j) {
      d.pb(sqr(X[i] - X[j]) + sqr(Y[i] - Y[j]));
    }
  }
  sort(all(d));
  return count(all(d), d[0]) >= 4;
}

void show(int b) {
  vector<int> v;
  rep (i, 8) if (b & (1 << i)) v.pb(i);
  rep (i, 4) printf("%d%c", v[i] + 1, i == 3 ? '\n' : ' ');
}

int main() {
  while (2 == scanf("%d%d", &X[0], &Y[0])) {
    for (int i = 1; i < 8; ++i) scanf("%d%d", &X[i], &Y[i]);

    const int all = (1 << 8) - 1;
    rep (b, 1 << 8) if (__builtin_popcount(b) == 4) {
      if (is_rectangle(b) && is_square(b) && is_rectangle(all ^ b)) {
        puts("YES");
        show(b);
        show(all ^ b);
        goto done;
      }
    }

    puts("NO");
 done:;
  }

  return 0;
}

