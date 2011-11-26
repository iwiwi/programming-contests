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
  string line;
  while (cin >> line && line != "#") {
    line += "X";
    int x = 0;
    rep (i, line.length() - 1) {
      if (isdigit(line[i]) && !isdigit(line[i + 1])) {
        x += (line[i] - '0') % 2;
      }
    }
    if (x % 2 == 0) puts("EVEN");
    else puts("ODD");
  }

  return 0;
}

