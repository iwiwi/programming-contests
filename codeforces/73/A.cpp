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
  ll v[3], K;
  cin >> v[0] >> v[1] >> v[2] >> K;
  sort(v, v + 3);

  ll w[3], k = K;
  rep (i, 3) {
    w[i] = min(v[i] - 1, (ll)floor(k / double(3 - i)));
    k -= w[i];
  }
  ll res = (w[0] + 1) * (w[1] + 1) * (w[2] + 1);
  cout << res << endl;

  return 0;
}

