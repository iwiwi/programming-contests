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
#define eb(e) emplace_back(e)
#define mp(a, b) make_pair(a, b)

int main() {
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    set<int> alive;
    for (int i = 1; i <= N; ++i) alive.insert(i);
    alive.insert(N + 10);

    vector<int> ans(N + 1);
    rep (i, M) {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);

      auto ite = alive.lower_bound(l);
      while (*ite <= r) {
        if (*ite == x) {
          ++ite;
        } else {
          ans[*ite] = x;
          alive.erase(ite++);
        }
      }
    }

    for (int i = 1; i <= N; ++i) printf("%d%c", ans[i], i == N ? '\n' : ' ');
  }
}
