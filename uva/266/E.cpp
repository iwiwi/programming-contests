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
  for (;;) {
    int T;
    scanf("%d", &T);
    if (T == 0) return 0;
    ++T;

    int A[30];
    rep (i, T) scanf("%d", A + i);

    double x = 0.0;
    rep (iter, 1000) {
      double y = 0.0;
      for (int i = T - 1; i >= 0; --i) y = y * x + A[i];

      double dy = 0.0;
      for (int i = T - 1; i >= 1; --i) dy = dy * x + A[i] * i;

      x -= y / dy;
    }

    printf("%.2f\n", 1 / x - 1);
  }

  return 0;
}

