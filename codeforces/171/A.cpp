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

int len(ll x) {
  int l = 1;
  for (x /= 10; x > 0; x /= 10) l++;
  return l;
}

ll rev(ll x) {
  ll r = 0;
  for (; x > 0; x /= 10) r = r * 10 + x % 10;
  return r;
}
ll pow10(int p) {
  ll r = 1;
  for (; p > 0; p--) r *= 10;
  return r;
}

int main() {
  for (ll A, B; cin >> A >> B; ) {
    B = rev(B);
    cout << A + B << endl;
  }

  return 0;
}

