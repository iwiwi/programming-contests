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

typedef long long ll;


int main() {
  int N, x, M, y;
  while (4 == scanf("%d%d%d%d", &N, &x, &M, &y)) {
    if (x > y) {
      swap(N, M);
      swap(x, y);
    }

    ll res = 1;
    // single
    for (int r = 0; r < N; ++r) {
      if (x - r - 1 < y - M) ++res;
    }
    for (int r = 0; r < M; ++r) {
      if (x + N < y + r + 1) ++res;
    }
    // printf(" %d\n", res);

    // kyoutsuu-bubun
    for (int r = 0; r < N; ++r) {
      int inr;
      if (x + r < y) inr = y - (x + r);
      else inr = (x + r + 1) - y;
      if (M >= inr) ++res;

      int outr = y - (x - r - 1);
      if (M >= outr) ++res;

      // printf("  %d %d\n", inr, outr);

      res += 2 * max(0, min(outr - 1, M) - inr);
      // printf(" %d: %d\n", r, res);
    }

    cout << res << endl;
  }

  return 0;
}

