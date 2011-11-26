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

const int cx[4] = {1, 0, 1,  1};
const int cy[4] = {0, 1, 1, -1};

int main() {
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    map<int, vector<pair<int, int> > > vs[4];
    vector<int> ans(M);

    rep (i, M) {
      int x, y;
      scanf("%d%d", &x, &y);
      rep (j, 4) {
        int a = cx[j    ] * x + cy[j    ] * y;
        int b = cx[j ^ 1] * x + cy[j ^ 1] * y;
        vs[j][a].pb(mp(b, i));
      }
    }

    rep (j, 4) {
      tr (vs[j], ite) {
        vector<pair<int, int> > &v = ite->second;
        sort(v.begin(), v.end());
        int n = v.size();
        rep (i, n) {
          int k = v[i].second, t = 2;
          if (i == 0) --t;
          if (i + 1 == n) --t;
          ans[k] += t;
        }
      }
    }

    rep (i, 9) printf("%d%c",
                      (int)count(all(ans), i),
                      i == 8 ? '\n' : ' ');
  }

  return 0;
}

