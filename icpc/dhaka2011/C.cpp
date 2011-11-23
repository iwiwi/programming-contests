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

#define A(x) (x[t[0]][t[1]][t[2]][t[3]][j0][j1])

const int tot[5] = {13, 13, 13, 13, 2};

int req[5];
bool vis[14][14][14][14][5][5];
double mem[14][14][14][14][5][5];

double search(int t[], int j0, int j1) {
  if (A(vis)) return A(mem);

  rep (i, 4) if (t[i] + (j0 == i) + (j1 == i) < req[i]) goto ng;
  return 0.0;

ng:
  int r = 0;
  rep (i, 5) r += tot[i] - t[i];
  if (r == 0) return 1E10;  // impossible...

  double res = 1.0;
  rep (i, 5) {
    if (tot[i] == t[i]) continue;

    double p = (tot[i] - t[i]) / double(r);
    double e = 1E10;
    if (i < 4) {
      ++t[i];
      e = search(t, j0, j1);
      --t[i];
    } else {
      rep (j, 4) {
        int tj0 = t[4] == 0 ? j : j0;
        int tj1 = t[4] == 1 ? j : j1;
        ++t[4];
        e = min(e, search(t, tj0, tj1));
        --t[4];
      }
    }
    // printf(" %f %f\n", p, e);
    res += p * e;
  }

  // rep (i, 5) printf("%d ", t[i]); printf(": %lf\n", res);
  assert(res > 0.0);


  A(vis) = true;
  return A(mem) = res;
}

int main() {
  int T;
  scanf("%d", &T);
  rep (ca, T) {
    rep (i, 4) scanf("%d", req + i);
    req[4] = 0;

    int t[5] = {0};
    memset(vis, 0, sizeof(vis));
    double res = search(t, 4, 4);

    printf("Case %d: ", ca + 1);
    if (res > 1E10) puts("-1.000");
    else printf("%.3f\n", res);
  }

  return 0;
}
