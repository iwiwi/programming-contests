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

const int M = 1100000;  // >= sqrt(U)
bool isnp_lo[1100000];
bool isnp_hi[1100000];  // x is prime <=> isnp_hi[x - L] = false

void init() {
  isnp_lo[1] = true;
  for (ll i = 2; i * i <= M; ++i) {
    if (isnp_lo[i]) continue;
    for (ll j = i; i * j <= M; ++j) isnp_lo[i * j] = true;
  }
}

ll rest[1100000];
int prv[1100000];
bool ng[1100000];

void sieve(ll L, ll U) {  // [L, U]
  for (ll i = L; i <= U; ++i) {
    rest[i - L] = i;
    prv[i - L] = 100;
    ng[i - L] = false;
  }

  ll n = ceil(sqrt(U));
  memset(isnp_hi, 0, sizeof(isnp_hi));
  if (L <= 1) isnp_hi[1 - L] = true;
  for (ll i = 2; i <= n; ++i) {
    if (isnp_lo[i]) continue;

    ll j = max(2LL, (L / i) + (L % i ? 1 : 0));

    for (; i * j <= U; ++j) {
      ll t = i * j;
      isnp_hi[t - L] = true;

      if (ng[t - L]) continue;

      ll &x = rest[t - L];
      int c = 0;
      while (x % i == 0) {
        ++c;
        x /= i;
      }
      int &p = prv[t - L];
      if (p < c) ng[t - L] = true;
      else p = c;
    }
  }

  // for (ll i = L; i <= U; ++i) {
  //   if (rest[i - L] != 1) {
      
  //   }
  // }
}

int main() {
  init();

  ll A, B;
  cin >> A >> B;
  ll L = max(A - B, 2LL);
  ll U = A + B;
  sieve(L, U);

  ll ans = 0;
  // for (ll i = L; i <= U; ++i) {
  //   vector<pair<ll, ll> > &f = factor[i - L];
  //   sort(all(f));

  //   // printf("%lld:\n", i);rep (j, f.size()) printf(" %lld %lld\n", f[j].first, f[j].second);
    
  //   rep (j, f.size() - 1) {
  //     if (f[j].second < f[j + 1].second) goto ng;
  //   }
  //   ++ans;
  // ng:;
  // }
  for (ll i = L; i <= U; ++i) if (!ng[i - L]) ++ans;
  cout << ans << endl;

  return 0;
}
