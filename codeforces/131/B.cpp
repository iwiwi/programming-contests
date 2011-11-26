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
  int N;
  while (1 == scanf("%d", &N)) {
    map<int, ll> ma;
    rep (i, N) {
      int x;
      scanf("%d", &x);
      ++ma[x];
    }

    ll a = ma[0] * (ma[0] - 1) / 2;
    for (int i = 1; i <= 100; ++i) a += ma[i] * ma[-i];
    cout << a << endl;
  }

  return 0;
}

