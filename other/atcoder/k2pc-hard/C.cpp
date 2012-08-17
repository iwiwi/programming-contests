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
  ll N;
  while (cin >> N) {
    if (N == 2) {
      puts("0");
      continue;
    }

    vector<pair<ll, ll> > ps;
    for (ll i = 2; i * i <= N; ++i) ps.pb(mp(i, i * i));

    if (ps.empty() || ps.back().second != N) {
      puts("-1");
      continue;
    }

    ll res = 0, now = 2;
    reverse(all(ps));
    rep (i, ps.size()) {
      res += ps[i].second - now + 1;
      now = ps[i].first;
    }
    printf("%lld\n", res);
  }

  return 0;
}

