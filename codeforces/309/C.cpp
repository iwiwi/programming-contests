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

const int K = 35;

ll A[40], B[40];

void addit(ll x, ll *a) {
  rep (i, K) if (x & (1LL << i)) ++a[i];
}

int main() {
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));

    {
      int a;
      rep (i, N) { scanf("%d", &a); addit(a, A); }
      rep (i, M) { scanf("%d", &a); ++B[a]; }
    }
    // rep (k, K) printf("%d ", A[k]); puts("");

    ll lb = 0, ub = M + 1;
    while (ub - lb > 1) {
      ll X = (lb + ub) / 2;

      ll b[40];
      {
        ll x = X;
        rep (i, K) {
          b[i] = min(B[i], x);
          x -= b[i];
        }
      }

      ll a[40] = {};
      for (int i = K - 1; i >= 0; --i) {
        a[i] += A[i];
        if (a[i] < b[i]) goto dmp;
        a[i] -= b[i];

        if (i > 0) a[i - 1] += a[i] * 2;
      }

      lb = X;
      continue;
   dmp:
      ub = X;
    }

    printf("%d\n", (int)lb);
  }

  return 0;
}

