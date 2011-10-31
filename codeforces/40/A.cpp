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
  int x, y;
  while (2 == scanf("%d%d", &x, &y)) {
    int r = round(sqrt(x*x + y*y));
    if (r*r == x*x + y*y || x == 0 || y == 0) {
      puts("black");
      continue;
    }

    r = floor(sqrt(x*x + y*y));
    if ((r % 2 == 0) ^ (x * y < 0)) puts("black");
    else puts("white");
  }

  return 0;
}

