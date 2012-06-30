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

ll choose(ll n, ll k) {
  ll res = 1;
  for (int i = 0; i < k; ++i) res = res * (n - i) / (i + 1);
  return res;
}

bool test(ll n, ll m, ll k) {
  ll s = 0;
  for (ll i = 0; i <= k; ++i) {
    ll t = min(n, choose(k, i));
    n -= t;
    s += t * i;
    if (n == 0) return s <= m * k;
  }
  return false;
}

int main() {
  int T;
  cin >> T;

  ll N, M;
  while (cin >> N >> M) {
    // M = min(M, N - M);

    ll lb = -1, ub = N;
    while (ub - lb > 1) {
      ll md = (lb + ub) / 2;
      if (test(N, M, md)) ub = md;
      else lb = md;
    }
    cout << ub << endl;
  }

  return 0;
}

