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

const ll K = 10000000000LL;
vector<ll> A;

void init(ll crr) {
  if (crr > K) return;
  A.pb(crr);
  init(crr * 10 + 4);
  init(crr * 10 + 7);
}

ll solve(ll M) {
  ll prv = 0, ans = 0;
  rep (i, A.size()) {
    ll k = max(0LL, min(A[i] + 1, M) - prv);
    ans += k * A[i];

    prv = A[i] + 1;
  }
  return ans;
}

int main() {
  ll L, R;
  cin >> L >> R;

  init(0);
  sort(all(A));

  ll sr = solve(R + 1);
  ll sl = solve(L);
  cout << sr - sl << endl;

  return 0;
}

