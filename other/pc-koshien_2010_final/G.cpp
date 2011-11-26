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

int X, Y, Z;
int V[10];
int evt[60], par[60];

bool vis[60][6010];
double mem[60][6010];

double saiki(int p, int m) {
  if (p >= Y) return m;  // goooooooooooal
  if (vis[p][m]) return mem[p][m];

  double sum = 0.0;
  rep (i, X) {
    int tp = p + V[i];
    int tm = m;
    if (tp < Y) {
      switch (evt[tp]) {
        case 1: tp += par[tp]; break;
        case 2: tm += par[tp]; break;
        case 3: tm = max(0, tm - par[tp]); break;
      }
    }
    sum += saiki(tp, tm);
  }

  vis[p][m] = true;
  // printf(" %d: %f\n", p, sum / X);
  return mem[p][m] = sum / X;
}

int main() {
  for (;;) {
    scanf("%d%d%d", &X, &Y, &Z);
    if (X == 0 && Y == 0 && Z == 0) return 0;
    // printf("%d %d %d !!!!!\n", X, Y, Z);

    rep (i, X) {
      scanf("%d", V + i);
      // printf("hoge: %d\n", V[i]);
    }

    memset(evt, 0, sizeof(evt));
    rep (i, Z) {
      int n, e, a;
      scanf("%d%d%d", &n, &e, &a);
      evt[n] = e;
      par[n] = a;
    }

    memset(vis, 0, sizeof(vis));
    double res = saiki(0, 0);
    printf("%.f\n", floor(res));
  }

  return 0;
}

