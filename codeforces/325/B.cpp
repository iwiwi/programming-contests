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
typedef long double ld;

int main() {
  ll N;
  while (cin >> N) {
    vector<ll> ans;

    for (int a = 0; ; ++a) {
      ll b = (1LL << a) - 1;
      if (b > N) break;

      ll lb = 0, ub = N;
      while (ub - lb > 1) {
        ll x = lb + (ub - lb) / 2;
        ld y = x * ld(x - 1) / 2 + b * ld(x);

        if (y >= N) ub = x;
        else lb = x;
      }

      if (ub * (ub - 1) / 2 + b * ub == N && ub % 2 == 1) {
        ans.pb(ub << a);
      }
    }

    sort(all(ans));
    if (ans.empty()) cout << "-1" << endl;
    else {
      rep (i, ans.size()) cout << ans[i] << endl;
    }
  }

  return 0;
}

