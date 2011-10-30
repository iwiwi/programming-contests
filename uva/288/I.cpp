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

typedef unsigned long long ull;

ull cum_xor(ull n) {
  switch (n % 4) {
  case 0: return n;
  case 1: return 1;
  case 2: return n + 1;
  case 3: return 0;
  }
  assert(false);
}


// [L, U]
ull solve(ull L, ull U) {
  ull ans = 0;

  for (int k = 1; k <= 63; ++k) {
    ull lb = max(L, ull(1) << (k - 1));
    ull ub = min(U, (ull(1) << k) - 1);
    // [lb, ub]
    if (U < lb) break;
    if (lb > ub) continue;

    // cout << lb << " " << ub << endl;
    // cout << " " << lb - 1 << ": " << cum_xor(lb - 1) << endl;
    // cout << " " << ub     << ": " << cum_xor(ub) << endl;

    ans <<= 1;
    // cout << " ans: " << ans << endl;
    ans ^= cum_xor(ub) ^ cum_xor(lb - 1);
  }
  // cout << X << ": " << ans << endl;
  return ans;
}

int main() {
  int T;
  cin >> T;

  rep (ca, T) {
    ull P, Q;
    cin >> P >> Q;

    ull ans = solve(P, Q);
    cout << "Case " << (ca + 1) << ": " << ans << endl;
  }

  return 0;
}

