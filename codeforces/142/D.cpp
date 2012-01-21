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
  int H, W, K;
  while (3 == scanf("%d%d%d", &H, &W, &K)) {
    bool g_can_draw, r_can_draw;
    g_can_draw = false;  // G = Shrek = First
    r_can_draw = false;  // R = Donkey = Second

    int x[20] = {};

    rep (y, H) {
      char buf[1024];
      scanf("%s", buf);

      int g = count(buf, buf + W, 'G');
      int r = count(buf, buf + W, 'R');
      if (!g && !r);
      else if (g && !r) g_can_draw |= W > g;
      else if (r && !g) r_can_draw |= W > r;
      else {
        int d = find(buf, buf + W, 'R') - find(buf, buf + W, 'G');
        d = abs(d) - 1;
        rep (i, 20) x[i] += (d >> i) & 1;
      }
    }

    if (g_can_draw && r_can_draw) {
      puts("Draw");
    } else if (g_can_draw) {
      puts("First");
    } else if (r_can_draw) {
      puts("Second");
    } else {
      rep (i, 20) if (x[i] % (K + 1)) {
        puts("First");
        goto done;
      }
      puts("Second");
   done:;
    }
  }

  return 0;
}

