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

ll solve_max(ll a, ll b, ll x) {
  if (a > b) swap(a, b);
  ll s = x / (a + b);
  ll r = x % (a + b);
  if (r < a) return s * 2 + 1;
  else return s * 2 + 2;
}

ll solve_min(ll a, ll b, ll x) {
  if (a > b) swap(a, b);
  ll s = x / (a + b);
  ll r = x % (a + b);
  if (r >= b) return 1 + s * 2;
  else return s * 2;
}

int main() {
  for (;;) {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a == 0 && b == 0 && c == 0 && d == 0) return 0;

    ll mi, ma;
    if (c == d) {
      mi = solve_min(a, b, c + d);
      ma = solve_max(a, b, c + d);
    }
    else {
       mi = min(solve_min(a, b, c + d), solve_min(a, b, abs(c - d)));
       ma = max(solve_max(a, b, c + d), solve_max(a, b, abs(c - d)));
    }
    cout << mi << " " << ma << endl;
  }

  return 0;
}

