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

// (0, 0) is the 0-th
pair<ll, ll> get(ll k) {  // 0-indexed
  for (ll s = 1; ; ++s) {
    if (k < s) return mp(k, s - k - 1);
    k -= s;
  }
}

ll get(pair<ll, ll> p) {
  ll s = p.first + p.second;
  return s * (s + 1) / 2 + p.first;
}

int main() {
  ll a, b;
  while (cin >> a >> b) {
    pair<ll, ll> p = get(a - 1);
    pair<ll, ll> q = get(b - 1);
    pair<ll, ll> r = mp(p.first + q.first+ 1, p.second + q.second + 1);
    cout << 1 + get(r) << endl;
  }

  return 0;
}

