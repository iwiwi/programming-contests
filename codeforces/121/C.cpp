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

const ll K = 10000000000LL;
vector<ll> L;

void init(ll crr) {
  if (crr > K) return;
  if (crr != 0) L.pb(crr);
  init(crr * 10 + 4);
  init(crr * 10 + 7);
}

bool is_lucky(ll x) {
  if (x == 0) return false;
  while (x > 0) {
    if (x % 10 != 4 && x % 10 != 7) return false;
    x /= 10;
  }
  return true;
}




ll fact(ll k) {
  ll res = 1;
  for (int i = 1; i <= k; ++i) res *= i;
  return res;
}

vector<int> kth_permutation(int n, ll k) {
  vector<int> res(n), num(n);
  rep (i, n) num[i] = i;
  if (k >= fact(n)) return vector<int>();

  rep (i, n) {
    ll f = fact(n - i - 1);
    res[i] = num[k / f];
    num.erase(num.begin() + (k / f));
    k %= f;
  }
  return res;
}



ll perm_n, perm_m;
vector<int> perm_last;

bool init_permutation(ll n, ll k) {
  perm_n = n;
  perm_last = kth_permutation(min(n, 20LL), k);  // 20! = 2.43 * 10^18
  if (perm_last.empty()) return false;

  perm_m = perm_n - perm_last.size();
  return true;
}

ll get_permutation(ll i) {
  if (i < perm_m) return i;
  else return perm_m + perm_last[i - perm_m];
}



int main() {
  init(0);

  ll N, K;
  while (cin >> N >> K) {
    // [1, N] -> [0, N)
    --K;

    if (!init_permutation(N, K)) {
      puts("-1");
      continue;
    }

    ll ans = 0;

    rep (i, L.size()) {
      ll l = L[i];
      if (1 <= l && l <= N && is_lucky(1 + get_permutation(l - 1))) ++ans;
    }

    cout << ans << endl;
  }

  return 0;
}

