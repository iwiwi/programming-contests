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

vector<int> F;

ll saiki(int n) {
  // printf(" n = %d\n", n);
  if (n == (int)F.size()) {
    ll k = 0;
    rep (i, F.size()) if (F[i]) k++;
    // printf(" k = %lld\n", k);
    return 1LL << k;
  }

  ll r1 = F[n] * saiki(n + 1);
  
  int t = 0;
  swap(t, F[n]);
  ll r2 = saiki(n + 1);
  swap(t, F[n]);

  return r1 + r2;
}

int main() {
  for (;;) {
    ll L;
    scanf("%lld", &L);
    if (!L) return 0;

    F.clear();
    for (ll i = 2; i * i <= L; ++i) {
      if (L % i == 0) {
        F.pb(0);
        while (L % i == 0) {
          ++F.back();
          L /= i;
        }
      }
    }
    if (L != 1) F.pb(1);

    printf("%lld\n", (saiki(0) + 1) / 2);
  }
  
  return 0;
}

