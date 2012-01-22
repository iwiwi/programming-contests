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

typedef pair<int, int> P;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

P X[3000];
int D[3000];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    char c;
    scanf("%d%d %c", &X[0].first, &X[0].second, &c);
    const char *RULD = "RULD";
    D[0] = strchr(RULD, c) - RULD;

    int N;
    scanf("%d", &N);

    rep (i, N) {
      char c;
      scanf("%d%d %c", &X[i + 1].first, &X[i + 1].second, &c);
      const char *RULD = "RULD";
      D[i + 1] = strchr(RULD, c) - RULD;
    }
    ++N;
    rep (i, N) X[i] = mp(X[i].first * 2, X[i].second * 2);

    for (int T = 1; T <= 450; ++T) {
      rep (i, N) {
        X[i].first  += dx[D[i]];
        X[i].second += dy[D[i]];

        if (i > 0 && X[i] == X[0]) {
          printf("%.1f\n", T / 2.0);
          goto done;
        }
      }
    }
    puts("SAFE");
 done:;
  }

  return 0;
}

