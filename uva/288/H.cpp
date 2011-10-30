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
  int T;
  cin >> T;

  rep (ca, T) {
    cout << "Case " << (ca + 1) << ": ";

    ll K;
    cin >> K;

    ll tax100 = 0, t;

    t = min(K, 180000LL);
    K -= t;

    t = min(K, 300000LL);
    tax100 += t * 10;
    K -= t;

    t = min(K, 400000LL);
    tax100 += t * 15;
    K -= t;

    t = min(K, 300000LL);
    tax100 += t * 20;
    K -= t;

    tax100 += K * 25;

    if (tax100 == 0) cout << "0" << endl;
    else if (tax100 < 100 * 2000) cout << "2000" << endl;
    else cout << (tax100 / 100 + (tax100 % 100 ? 1 : 0)) << endl;
  }

  return 0;
}

