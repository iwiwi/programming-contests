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

const int N = 8;

int main() {
  char r1, r2;
  int x1, x2;
  while (4 == scanf(" %c%d %c%d", &r1, &x1, &r2, &x2)) {
    int y1 = r1 - 'a';
    int y2 = r2 - 'a';
    --x1;
    --x2;
    
    int ans = 0;
    rep (y, N) rep (x, N) {
      if (y1 == y || x1 == x) continue;

      int dx1 = abs(x1 - x), dy1 = abs(y1 - y);
      int dx2 = abs(x2 - x), dy2 = abs(y2 - y);
      
      if (dx1 > dy1) swap(dx1, dy1);
      if (dx2 > dy2) swap(dx2, dy2);
      
      if (dx1 == 1 && dy1 == 2) continue;
      if (dx2 == 1 && dy2 == 2) continue;
      if (dx2 == 0 && dy2 == 0) continue;
      
      ++ans;
    }
    printf("%d\n", ans);
  }
  
  return 0;
}

