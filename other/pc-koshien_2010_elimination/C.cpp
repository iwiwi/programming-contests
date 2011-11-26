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
    int N;
    scanf("%d", &N);
    if (N == 0) return 0;

    rep (i, N) {
      int m, e, j;
      scanf("%d%d%d", &m, &e, &j);
      if (m == 100 || e == 100 || j == 100) goto A;
      if (m + e >= 90 * 2) goto A;
      if (m + e + j >= 80 * 3) goto A;
      if (m + e + j >= 70 * 3) goto B;
      if (m + e + j >= 50 * 3 && (m >= 80 || e >= 80)) goto B;

      puts("C");
      continue;
    A:
      puts("A");
      continue;
    B:
      puts("B");
      continue;
    }
  }

  return 0;
}

