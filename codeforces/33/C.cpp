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

int N, A[100010];
ll dp1[100010], dp2[100010];

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", A + i);

    {
      ll tot = 0, prv = 0;
      rep (i, N) {
        tot += A[i];
        prv = dp1[i] = max(prv + A[i], -tot);
      }
    }
    {
      ll tot = 0, prv = 0;
      for (int i = N - 1; i >= 0; --i) {
        tot += A[i];
        prv = dp2[i] = max(prv + A[i], -tot);
      }
    }

    ll ans = -987654321987654321LL;
    rep (i, N) ans = max(ans, dp1[i] + dp2[i + 1]);
    cout << ans << endl;
  }
  
  return 0;
}

