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
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    vector<pair<pair<int, int>, int> > itvs(M);
    rep (i, M) {
      int r, c;
      scanf("%d%d", &r, &c);
      int d = (r + c) - (N + 1);
      itvs[i].first = mp(r + 1, r - d);
      itvs[i].second = i;
    }
    sort(all(itvs));

    set<int> se;
    for (int i = 1; i <= N; ++i) se.insert(i);
    vector<int> ans;

    rep (i, M) {
      int b = itvs[i].first.second;
      int e = itvs[i].first.first;
      // [b, e)
      // printf("%d: [%d, %d)\n", itvs[i].second, b, e);

      iter(se) ite = se.lower_bound(b);
      if (ite == se.end() || e <= *ite) continue;

      se.erase(ite);
      ans.pb(itvs[i].second);
    }

    printf("%d\n", (int)ans.size());
    rep (i, ans.size()) printf("%d%c", ans[i] + 1, i + 1 == ans.size() ? '\n' : ' ');
  }

  return 0;
}

