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
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

void hoge() {
  const int M = 110;
  vector<int> prv(M + 1), nxt(M + 1);
  prv[1] = 1;

  for (int i = 1; i < M; ++i) {
    for (int j = 1; j <= M; ++j) {
      if (j == 1) {
        nxt[j] = prv[j + 1];
      } else if (j == M) {
        nxt[j] = prv[j - 1];
      } else {
        nxt[j] = prv[j - 1] ^ prv[j + 1];
      }
    }

    int s = accumulate(all(nxt), 0);
    printf("%d: %d, %d\n", i, s, 1 << (__builtin_popcount(i + 1) - 1));

    prv.swap(nxt);
  }
}

ll cmb(ll n, int k) {  // n choose k
  if (k < 0 || k > n) return 0;
  ll res = 1;
  for (int i = 0; i < k; ++i) res = res * (n - i) / (i + 1);
  return res;
}

// popcount(x) == p, 0 <= x <= n
ll solve(ll n, int p) {
  if (p == 0) return 1;
  else if (n == 0) return 0;
  else {
    int b = 63 - __builtin_clzll(n);
    return solve(n - (1LL << b), p - 1) + cmb(b, p);
  }
}

int main() {
  // hoge();

  ll N, T;
  while (cin >> N >> T) {
    int P = 0;
    while (T > 1 && T % 2 == 0) {
      ++P;
      T /= 2;
    }
    if (T != 1) {
      puts("0");
      continue;
    }
    // T = 2 ** P

    ll ans = solve(N + 1, P + 1) - solve(1, P + 1);
    cout << ans << endl;
  }

  return 0;
}

