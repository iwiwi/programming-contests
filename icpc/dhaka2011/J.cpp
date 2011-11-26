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

int N;
bool adj[110][110];
int A[110];

int main() {
  int T;
  scanf("%d", &T);
  rep (ca, T) {
    int M;
    scanf("%d%d", &N, &M);
    rep (i, N) scanf("%d", A + i);

    memset(adj, 0, sizeof(adj));
    rep (i, M) {
      int a, b;
      scanf("%d%d", &a, &b);
      adj[a][b] = true;
    }

    int v = 0, s = 0;
    for (;;) {
      int w = -1, t = -1;
      rep (tv, N) {
        if (adj[v][tv] && A[tv] > t) {
          w = tv;
          t = A[tv];
        }
      }
      if (w == -1) break;
      v = w;
      s += t;
    }
    printf("Case %d: %d %d\n", ca + 1, s, v);
  }

  return 0;
}
