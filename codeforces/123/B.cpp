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

ll ABS(ll x) {
  if (x < 0) return -x;
  else return x;
}

int main() {
  ll A, B, X1, Y1, X2, Y2;
  while (cin >> A >> B >> X1 >> Y1 >> X2 >> Y2) {
    ll A2 = A * 2, B2 = B * 2;

    ll a1 = X1 + Y1, a2 = X2 + Y2;
    ll ma1 = (a1 % A2 + A2) % A2, ma2 = (a2 % A2 + A2) % A2;
    ll ga1 = (a1 - ma1) / A2, ga2 = (a2 - ma2) / A2;
    ll da = ABS(ga2 - ga1);

    ll b1 = X1 - Y1, b2 = X2 - Y2;
    ll mb1 = (b1 % B2 + B2) % B2, mb2 = (b2 % B2 + B2) % B2;
    ll gb1 = (b1 - mb1) / B2, gb2 = (b2 - mb2) / B2;
    ll db = ABS(gb2 - gb1);

    cout << max(da, db) << endl;
  }

  return 0;
}

