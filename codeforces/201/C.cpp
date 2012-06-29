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
const ll INF = 1LL << 60;

int N;

vector<ll> doit(ll *A) {
  vector<ll> res(N);
  res[0] = 0;
  ll t = 0;

  for (int i = 1; i < N; ++i) {
    ll a = A[i - 1];
    if (a == 1) t = 0;
    else t += a / 2 * 2;

    res[i] = max(t, res[i - 1] + (a % 2 == 0 ? a - 1 : a));
  }
  return res;
}

ll A[100010];

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N - 1) {
      int a;
      scanf("%d", &a);
      A[i] = a;
    }

    vector<ll> dp1 = doit(A);
    // rep (i, N) printf("%lld ", dp1[i]); puts("");

    reverse(A, A + (N - 1));
    vector<ll> dp2 = doit(A);
    reverse(all(dp2));
    // rep (i, N) printf("%lld ", dp2[i]); puts("");

    ll res = -INF;
    rep (i, N) res = max(res, dp1[i] + dp2[i]);
    cout << res << endl;
  }

  return 0;
}

