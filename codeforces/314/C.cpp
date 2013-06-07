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
const int MOD = 1000000007;

struct fenwick_tree {
  int n;
  int x[1000100];

  void init(int n_) {
    n = n_;
    memset(x, 0, sizeof(int) * n);
  }
  ll sum(int j) {  // [0, j)
    int S = 0;
    for (--j; j >= 0; j = (j & (j + 1)) - 1) (S += x[j]) %= MOD;
    return S;
  }
  void add(int k, int a) {  // 0 <= k < n
    for (; k < n; k |= k + 1) (x[k] += a) %= MOD;
  }
};

fenwick_tree ft;
ll prv[1000100];

int main() {
  for (int N; 1 == scanf("%d", &N); ) {
    ft.init(1000010);
    memset(prv, 0, sizeof(prv));
    ft.add(0, 1);

    rep (i, N) {
      int a;
      scanf("%d", &a);

      ll t = (ft.sum(a) * a) % MOD;
      (t += prv[a] * a) %= MOD;

      ft.add(a, (-prv[a] + t) % MOD);
      prv[a] = t;
    }

    ll ans = 0;
    for (int x = 1; x <= 1000010; ++x) (ans += prv[x]) %= MOD;
    cout << (ans + MOD) % MOD << endl;
  }

  return 0;
}

