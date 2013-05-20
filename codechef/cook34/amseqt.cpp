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

template <class T>
struct fenwick_tree {
  int n;
  T x[1000010];

  void init(int n_) {
    n = n_;
    memset(x, 0, sizeof(int) * n);
  }
  T sum(int j) {  // [0, j)
    T S = 0;
    for (--j; j >= 0; j = (j & (j + 1)) - 1) S += x[j];
    return S;
  }
  void add(int k, T a) {  // 0 <= k < n
    for (; k < n; k |= k + 1) x[k] += a;
  }
};

typedef long long ll;
ll MOD = 1000000009;

fenwick_tree<int> ft;

int main() {
  int T;
  scanf("%d", &T);
  rep (t, T) {
    int N, M;
    scanf("%d%d", &N, &M);
    int K = 1 << M;

    ft.init(K);

    int P = 0;
    ft.add((0 - P + K) % K, 1);
    ll ans = 0;

    rep (i, N) {
      int A;
      scanf("%d", &A);

      (P += A) %= K;
      int l = 0, r = 1 << (M - 1);  // [l, r)
      l = (l - P + K) % K;
      r = (r - P + K) % K;

      ans = 0;
      ans += ft.sum(r);
      ans -= ft.sum(l);
      if (r <= l) ans += ft.sum(K);
      ans %= MOD;

      ft.add((0 - P + K) % K, ans);
    }

    cout << (ans + MOD) % MOD << endl;
  }

  return 0;
}

