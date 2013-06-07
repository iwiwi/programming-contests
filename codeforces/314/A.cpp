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

typedef long long ll;
typedef long double ld;

ll A[1000010];

int main() {
  int N, K;
  while (2 == scanf("%d%d", &N, &K)) {
    for (int i = 1; i <= N; ++i) {
      int a;
      scanf("%d", &a);
      A[i] = a;
    }

    ll i = 1, n = N;

    ll sumll = 0;
    ld sumld = 0;
    for (int k = 1; k <= N; ++k) {
      ll ai = A[k];
      ld dld = sumld - (n - i) * ld(ai) * (i - 1);

      // if (ai != 0) fprintf(stderr, "%d: %lld -> %.f\n", k, ai, (double)dld);

      if (dld >= 1E9) continue;
      ll dll = sumll - (n - i) * ll(ai) * (i - 1);
      if (dld >= -1E10 && dll >= K) {
        sumll += ai * ll(i - 1);
        sumld += ai * ld(i - 1);
        ++i;
      } else {

        --n;
        printf("%d\n", k);
      }
    }
  }

  return 0;
}

