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
  for (;;) {
    ll x;
    cin >> x;
    if (x == 0) return 0;

    string ans = "";


    if (x < 0) x *= -1;
    else {
      ans += '0' + x % 10;
      x /= 10;
    }

    while (x > 0) {
      ll t = x % 10;
      ans += '0' + (10 - t % 10) % 10;
      if (t > 0) x += 10;
      x /= 10;

      if (x == 0) break;
      ans += '0' + x % 10;
      x /= 10;
    }

    reverse(all(ans));
    cout << ans << endl;
  }

  return 0;
}

