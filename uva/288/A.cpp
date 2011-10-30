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

ll fact(ll k) {
  ll res = 1;
  for (int i = 1; i <= k; ++i) res *= i;
  return res;
}

vector<int> kth_permutation(int n, ll k) {
  vector<int> res(n), num(n);
  rep (i, n) num[i] = i;
  if (k >= fact(n)) return vector<int>();

  rep (i, n) {
    ll f = fact(n - i - 1);
    res[i] = num[k / f];
    num.erase(num.begin() + (k / f));
    k %= f;
  }
  return res;
}

int main() {
  int T;
  cin >> T;

  rep (ca, T) {
    string T;
    ll K;
    cin >> T >> K;
    --K;
    int N = T.length();

    vector<int> p = kth_permutation(N, K);

    string ans(N, 'X');
    rep (i, N) ans[p[i]] = T[i];
    cout << "Case " << (ca + 1) << ": " << ans << endl;
  }

  return 0;
}

