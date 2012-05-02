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

const char *ABXY = "ABXY";

int N;
int A[1010];


int main() {
  while (1 == scanf("%d", &N)) {
    memset(A, -1, sizeof(A));
    rep (i, N) {
      char c;
      scanf(" %c", &c);
      A[i] = strchr(ABXY, c) - ABXY;
    }

    int ans = N;
    rep (b, 4 * 4 * 4 * 4) {
      int lr[2][2] = { {b & 3, (b >> 2) & 3}, {(b >> 4) & 3, (b >> 6) & 3 }};
      // rep (i, 2) rep (j, 2) printf("%d ", lr[i][j]); puts("");

      int c = 0, p = 0;
      while (p < N) {
        rep (i, 2) {
          rep (j, 2) if (A[p + j] != lr[i][j]) goto ng;
          // match
          ++c;
          p += 2;
          goto done;
       ng:;
        }
        ++c;
        ++p;
        continue;
     done:;
      }

      ans = min(ans, c);
    }

    printf("%d\n", ans);
  }

  return 0;
}

