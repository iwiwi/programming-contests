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
    double a;
    scanf("%lf", &a);
    if (a < 0) return 0;

    rep (b, 1 << 12) {
      if (b / 16.0 == a) {
        for (int i = 11; i >= 4; --i) printf("%d", (b >> i) & 1);
        printf(".");
        for (int i = 3; i >= 0; --i) printf("%d", (b >> i) & 1);
        puts("");
        goto done;
      }
    }
    puts("NA");
  done:;
  }

  return 0;
}

