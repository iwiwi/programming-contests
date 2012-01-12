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

ll N, ma, mi;

void hoge(ll a, ll b, ll c) {
  ll t = (a + 1) * (b + 2) * (c + 2);
  ma = max(ma, t - N);
  mi = min(mi, t - N);
}

int main() {
  while (cin >> N) {
    ma = 0;
    mi = 1LL << 60;

    for (ll a = 1; a * a * a <= N; ++a) {
      for (ll b = a; a * b * b <= N; ++b) {
        ll c = N / a / b;
        if (a * b * c != N) continue;

        hoge(a, b, c);
        hoge(b, c, a);
        hoge(c, a, b);
      }
    }

    cout << mi << " " << ma << endl;
  }

  return 0;
}

