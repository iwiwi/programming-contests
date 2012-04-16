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


int N, K;
int C[1010], T[1010];
vector<pair<int, int> > ss, ps;

int main() {
  while (2 == scanf("%d%d", &N, &K)) {
    ss.clear();
    ps.clear();
    rep (i, N) {
      scanf("%d%d", &C[i], &T[i]);
      if (T[i] == 1) ss.pb(mp(C[i], i));
      else           ps.pb(mp(C[i], i));
    }

    sort(all(ss));
    sort(all(ps));

    vector<int> ans[1010];
    rep (i, ss.size()) ans[max(K - i - 1, 0)].pb(ss[(int)ss.size() - i - 1].second);

    int ub = max(0, K - (int)ss.size() - 1);
    rep (i, ps.size()) ans[min(i, ub)].pb(ps[i].second);

    double sum = 0.0;
    rep (i, K) {
      bool d = false;
      double su = 0.0, mi = 1E30;
      rep (j, ans[i].size()) {
        int k = ans[i][j];
        d |= T[k] == 1;
        su += C[k];
        mi = min(mi, (double)C[k]);
      }
      sum += su;
      if (d) sum -= mi / 2;
    }
    printf("%.1f\n", sum);
    rep (i, K) {
      printf("%d", (int)ans[i].size());
      rep (j, ans[i].size()) printf(" %d", 1 + ans[i][j]);
      puts("");
    }
  }

  return 0;
}

