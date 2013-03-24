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
  int T;
  scanf("%d", &T);
  rep (t, T) {
    int N, C, Q;
    scanf("%d%d%d", &N, &C, &Q);
    int x = --C;

    rep (i, Q) {
      int l, r;
      scanf("%d%d", &l, &r);
      --l;
      if (l <= x && x < r) {
        x = l + ((r - l) - (x - l) - 1);
      }
    }

    printf("%d\n", x + 1);
  }

  return 0;
}
