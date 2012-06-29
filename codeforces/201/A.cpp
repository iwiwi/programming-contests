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

ll f(ll n) {
  if (n % 2 == 1) {
    return (n * n + 1) / 2;
  } else {
    ll m = n / 2 - 1;
    return (m * m + 1) / 2 * 4;
  }
}

int main() {
  // for (int n = 1; n <= 15; ++n) {
  //   printf("%d: %lld\n", n, f(n));
  // }

  ll X;
  while (cin >> X) {
    if (X == 3) {
      puts("5") ;
    } else {
      for (ll N = 1; ; ++N) {
        if (f(N) >= X) {
          cout << N << endl;
          break;
        }
      }
    }
  }

  return 0;
}

