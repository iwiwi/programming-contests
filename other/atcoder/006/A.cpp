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
    vector<int> E(6);
    int B;
    rep (i, 6) if (!(cin >> E[i])) return 0;
    cin >> B;

    int c = 0, b = 0;
    rep (i, 6) {
      int l;
      scanf("%d", &l);
      if (cpresent(E, l)) ++c;
      else if (l == B) ++b;
    }

    if (c == 6) puts("1");
    else if (c == 5 && b == 1) puts("2");
    else if (3 <= c) printf("%d\n", 8 - c);
    else puts("0");
  }

  return 0;
}

