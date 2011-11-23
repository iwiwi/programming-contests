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

int pop_pre[1 << 20];

void init_pop(int n) {  // n bits
  for (int b = 1; b < 1 << n; ++b) {
    pop_pre[b] = pop_pre[b & (b - 1)] + 1;
  }
}

inline int pop(int b) {
  return pop_pre[b];
}

int N, M;
int adj[20];

int ine[1 << 18], sub[1 << 18], prv[1 << 18];

int main() {
  init_pop(18);

  int T;
  scanf("%d", &T);

  rep (ca, T) {
    scanf("%d%d", &N, &M);

    memset(adj, 0, sizeof(adj));
    rep (i, M) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      adj[a] |= 1 << b;
      adj[b] |= 1 << a;
    }
    int all = (1 << N) - 1;

    ine[0] = 0;
    rep (b, 1 << N) if (b) {
      int v = __builtin_ctz(b);
      ine[b] = ine[b ^ (1 << v)] + pop(adj[v] & b);
    }

    int n2 = N / 2;
    int n4 = (n2 + 1) / 2;
    rep (b, 1 << N) if (pop(b) == n2) {
      sub[b] = -1;
      // printf(" b=%d\n", b);
      for (int tb = b; tb; tb = (tb - 1) & b) if (pop(tb) == n4) {
          int t = ine[tb] + ine[b ^ tb];
          // printf("  t=%d\n", t);
          if (t > sub[b]) {
            sub[b] = t;
            prv[b] = tb;
            // printf(" %d: %d\n", b, t);
          }
      }
    }

    int ans = -1, see = 0;
    rep (b, 1 << N) if (pop(b) == n2) {
      int t = sub[b] + sub[b ^ all];
      if (t > ans) {
        ans = t;
        see = b;
      }
    }

    int x[20], y[20];
    rep (i, N) {
      int b = 1 << i;
      int q = see & b ? (prv[see] & b ? 2 : 3) : (prv[all ^ see] & b ? 0 : 1);
      x[i] = (i + 1) * (q & 1 ? -1 : 1);
      y[i] = (i + 1) * (q & 2 ? -1 : 1);
    }

    if (ca) puts("");
    printf("%d\n", M - ans);
    rep (i, N) printf("%d %d\n", x[i], y[i]);
  }

  return 0;
}

