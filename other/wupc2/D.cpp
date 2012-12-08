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

int main() {
  ll N[6];
  while (cin >> N[1]) {
    for (int i = 2; i <= 5; ++i) cin >> N[i];

    ll ans = 0;

    // 5
    ans += N[5];

    // 4 + 1
    {
      ll k4 = N[4];
      ans += k4;
      ll k1 = min(N[1], k4 * (5*5*5 - 4*4*4));
      N[1] -= k1;
    }

    // 3 + 2 + 1
    {
      ll k3 = N[3];
      ans += k3;
      ll k2 = min(N[2], k3 * 7);
      N[2] -= k2;
      ll k1 = min(N[1], 5*5*5 * k3 - 3*3*3 * k3 - 2*2*2 * k2);
      N[1] -= k1;
    }

    // 2 + 1
    {
      ll k2 = N[2];
      ll t = k2 / 8 + (k2 % 8 ? 1 : 0);
      ans += t;
      ll k1 = min(N[1], 5*5*5 * t - 2*2*2 * k2);
      N[1] -= k1;
    }

    // 1
    {
      ll v = 5*5*5;
      ans += N[1] / v + (N[1] % v ? 1 : 0);
    }

    cout << ans << endl;
  }

  return 0;
}

