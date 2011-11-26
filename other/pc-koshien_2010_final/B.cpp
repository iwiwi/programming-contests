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
    int N, M;
    scanf("%d%d", &N, &M);
    if (N == 0 && M == 0) return 0;
    deque<int> P(N);
    rep (i, N) scanf("%d", &P[i]);
    sort(all(P));

    int ans = 0;
    while (P.size() % M > 0) {
      ans += P.front();
      P.pop_front();
    }
    while (!P.empty()) {
      P.pop_front();
      rep (i, M - 1) {
        ans += P.front();
        P.pop_front();
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}

