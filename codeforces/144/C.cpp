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
  string S, P;
  while (cin >> S >> P) {
    int sl = S.length();
    int pl = P.length();
    if (pl > sl) {
      puts("0");
      continue;
    }

    int sc[256] = {}, pc[256] = {};
    rep (i, pl) {
      sc[S[i]]++;
      pc[P[i]]++;
    }

    int ans = 0;
    for (int b = 0; b + pl <= sl; ++b) {
      // [b, b + pl)
      rep (i, 26) if (sc['a' + i] > pc['a' + i]) {
        // printf("%d %d: %d %d\n", b, i, sc['a' + i], pc['a' + i]);
        goto ng;
      }
      ++ans;
   ng:
      if (b + pl < sl) {
        --sc[S[b]];
        ++sc[S[b + pl]];
      }
    }

    printf("%d\n", ans);
  }

  return 0;
}

