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

pair<ll, ll> solve(ll s, int n) {
  ll state, x, y, row;
  state = x = y = 0;

  for (int i = 2 * n - 2; i >= 0; i -= 2) {
    row = 4 * state | (s >> i) & 3;
    x = (x << 1) | (0x936C >> row) & 1;
    y = (y << 1) | (0x39C6 >> row) & 1;
    state = (0x3E6B94C1 >> 2 * row) & 3;
  }

  return mp(x, y);
}

int main() {
  for (ll a, b; cin >> a >> b; ) {
    pair<ll, ll> ans = solve(b, a);
    cout << ans.first << " " << ans.second << endl;
  }


  return 0;
}

