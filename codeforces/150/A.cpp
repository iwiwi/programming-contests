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
  for (ll Q; cin >> Q; ) {
    vector<ll> ds;
    ll t = Q;
    for (ll i = 2; i * i <= t; ++i) {
      while (t % i == 0) {
        ds.push_back(i);
        t /= i;
      }
    }
    if (t > 1) ds.push_back(t);

    if (ds.size() == 2) {
      puts("2");
    } else if (ds.size() <= 1) {
      puts("1");
      puts("0");
    } else {
      ll x = 1;
      rep (i, 2) x *= ds[i];
      cout << 1 << endl;
      cout << x << endl;
    }
  }

  return 0;
}

