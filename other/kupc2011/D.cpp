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
int C[1010][1010];
int tmp[1010];

int main() {
  srand(123123);

  while (2 == scanf("%d%d", &N, &K)) {
    rep (i, K) rep (j, N / 2) {
      scanf("%d", &C[i][j]);
      --C[i][j];
    }

    for (;;) {
      rep (i, N) tmp[i] = (rand() >> 10) & 1;

      rep (i, K) {
        int s = 0;
        rep (j, N / 2) s += tmp[C[i][j]];
        if (s < N / 8 || 3 * N / 8 < s) goto ng;
      }

      rep (i, N) printf("%d", tmp[i]); puts("");
      break;
    ng:
      ;
    }
  }
}
