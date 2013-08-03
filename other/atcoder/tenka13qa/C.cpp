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

int W, H;
int fld[1010][1010];

int ans;

void search(int x, int y) {
  if (y == H) ++ans;
  else if (x == W) search(0, y + 1);
  else {
    for (int c = 1; c <= 3; ++c) {
      fld[y][x] = c;
      for (int d = 1; d <= c; ++d) {
        if (y - d >= 0 && fld[y - d][x] == c) goto dmp;
        if (x - d >= 0 && fld[y][x - d] == c) goto dmp;
      }
      search(x + 1, y);
   dmp:;
    }
  }
}

int solve(int w, int h) {
  if (w > h) swap(w, h);

  if (w <= 5 && h <= 5) {
    W = w;
    H = h;
    ans = 0;
    search(0, 0);
    return ans;
  } else if (w == 1) {
    const int ans[4] = {10, 9, 8, 9};
    return ans[h % 4];
  } else {
    const int ans[4] = {18, 20, 18, 16};
    return ans[(w + h) % 4];
  }
}

int main() {
  {
    int w, h;
    scanf("%d%d", &w, &h);
    printf("%d\n", solve(w, h));
  }

  if (0) {
    scanf("%d%d", &W, &H);
    search(0, 0);
    printf("%d\n", ans);
  }

  if (0) {
    for (int w = 1; w <= 50; ++w) {
      printf("%3d: ", W);
      for (int h = 1; h <= 50; ++h) {
        int tmp = solve(w, h);

        W = w;
        H = h;
        ans = 0;
        search(0, 0);
        printf("%5d(%d)", ans, (W + H) % 4);

        assert(ans == tmp);
      }
      puts("");
    }
  }


  return 0;
}

