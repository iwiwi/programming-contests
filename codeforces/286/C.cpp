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

int P[1000010];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", &P[i]);
    int T;
    scanf("%d", &T);
    rep (i, T) {
      int k;
      scanf("%d", &k);
      P[k - 1] *= -1;
    }

    stack<int> stk;
    for (int i = N - 1; i >= 0; --i) {
      if (P[i] > 0 && !stk.empty() && stk.top() == P[i]) {
        stk.pop();
      } else {
        P[i] = -abs(P[i]);
        stk.push(abs(P[i]));
      }
    }

    if (stk.empty()) {
      puts("YES");
      rep (i, N) printf("%d%c", P[i], i == N - 1 ? '\n' : ' ');
    } else {
      puts("NO");
    }
  }

  return 0;
}

