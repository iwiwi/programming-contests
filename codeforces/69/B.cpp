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
    map<int, vector<pair<pair<int, int>, int> > > ma;
    rep (k, M) {
      int l, r, t, c;
      scanf("%d%d%d%d", &l, &r, &t, &c);
      for (int i = l; i <= r; ++i) {
        ma[i].pb(mp(mp(t, k), c));
      }
    }

    int ans = 0;
    tr (ma, ite) {
      vector<pair<pair<int, int>, int> > &v = ite->second;
      // rep (i, v.size()) printf("  %d %d\n", v[i].first.first, v[i].first.second);
      ans += min_element(all(v))->second;
      // printf(" %d\n", min_element(all(v))->second);
    }
    printf("%d\n", ans);
  }

  return 0;
}

