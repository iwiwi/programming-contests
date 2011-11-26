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
    string s, t;
    cin >> s >> t;
    if (s == "0" && t == "0") return 0;

    int h = 0, b = 0;
    rep (i, 4) rep (j, 4) {
      if (s[i] == t[j]) {
        if (i == j) ++h;
        else ++b;
      }
    }
    printf("%d %d\n", h, b);
  }

  return 0;
}

