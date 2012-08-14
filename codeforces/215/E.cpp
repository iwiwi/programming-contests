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

const int MAX_N = 1000000;

int mu[MAX_N + 1];

void init_moebius(int n) {
  static bool isnp[MAX_N + 1] = {0};
  for (int i = 1; i <= n; ++i) mu[i] = 1;
  for (int i = 2; i <= n; ++i) if (!isnp[i]) {
    for (int j = i; j <= n; j += i) mu[j] *= -1, isnp[j] = true;
    for (ll j = i * (ll)i; j <= n; j += i * i) mu[j] = 0;
  }
}

ll s2b(string s) {  // [0] = MSB
  ll r = 0;
  rep (i, s.length()) r = r * 2 + (s[i] - '0');
  return r;
}

string b2s(ll u) {
  string b;
  while (u) {
    b += "01"[u % 2];
    u /= 2;
  }
  reverse(all(b));
  return b;
}

ll solve3(string u, int k) {
  int n = u.length();
  deque<string> v;
  for (int i = 0; i < n; i += k) v.pb(u.substr(i, k));
  string a = v.front();

  while (!v.empty() && v.front() == a) v.pop_front();

  assert(a[0] == '1');
  if (!v.empty() && a > v.front()) return s2b(a.substr(1));
  else return s2b(a.substr(1)) + 1;
}

ll solve2(string u) {
  int n = u.length();
  ll ans = 0;

  vector<ll> ts(n);
  for (int k = 1; k < n; ++k) {
    if (n % k != 0) continue;
    ts[k] = solve3(u, k);

    ll x = 0;
    for (int j = 1; j <= k; ++j) {
      if (k % j == 0) x += mu[k / j] * ts[j];
    }
    ans += x;
    // cout << u << "\t" << k << "\t" << x << endl;
  }

  return ans;
}

ll solve1(ll u) {  // [1, U]
  if (u == 0) return 0;

  string b = b2s(u);

  ll ans = 0;
  for (int l = 1; l < (int)b.length(); ++l) {
    ans += solve2(string(l, '1'));
  }
  ans += solve2(b);

  return ans;
}

namespace debug {
int init_kmp(const string &s) {
  int n = s.length();
  vector<int> next(n + 1);
  next[0] = -1;
  for (int i = 0, j = -1; i < n; next[++i] = ++j)
    while ((j >= 0) && (s[i] != s[j])) j = next[j];
  return n - next.back();
}

ll naive(ll l, ll r) {
  ll ans = 0;
  for (ll x = l; x <= r; ++x) {
    string s = b2s(x);
    int n = s.length(), k = init_kmp(s);
    if (k < n && n % k == 0) {
      cerr << " " << s << endl;
      ans += 1;
    }
  }
  return ans;
}
}

int main() {
  init_moebius(100);

  ll L, R;
  while (cin >> L >> R) {
    // cerr << debug::naive(L, R) << endl;
    ll ans = solve1(R) - solve1(L - 1);
    cout << ans << endl;
  }

  return 0;
}

