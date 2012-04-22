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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int main() {
  string S;
  while (cin >> S) {
    int l_lo = 0, r_hi = 0;
    rep (i, S.length()) if (isupper(S[i])) ++r_hi;

    int ans = INT_MAX;
    rep (i, S.length() + 1) {
      ans = min(ans, l_lo + r_hi);

      if (i < (int)S.length()) {
        if (islower(S[i])) ++l_lo;
        if (isupper(S[i])) --r_hi;
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}

