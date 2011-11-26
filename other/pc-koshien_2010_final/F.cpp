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
    int N;
    scanf("%d", &N);
    if (N == 0) return 0;

    vector<pair<int, int> > evt;
    rep (i, N) {
      int m, a, b;
      scanf("%d%d%d", &m, &a, &b);
      evt.pb(mp(a, m));
      evt.pb(mp(b, -m));
    }

    sort(all(evt));
    int tot = 0;
    rep (i, evt.size()) {
      tot += evt[i].second;
      if (tot > 150) goto ng;
    }

    puts("OK");
    continue;
 ng:
    puts("NG");
  }

  return 0;
}

