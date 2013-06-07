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
  int R1, R2;
  string W1, W2;
  while (cin >> R1 >> R2 >> W1 >> W2) {
    int L1 = W1.length(), L2 = W2.length();

    vector<int> fwd(L2);
    rep (i2, L2) {
      int f2 = 0;
      rep (i1, L1) if (W1[i1] == W2[(i2 + f2) % L2]) ++f2;
      fwd[i2] = f2;
    }

    ll i2 = 0;
    rep (r1, R1) i2 += fwd[i2 % L2];
    cout << i2 / (L2 * R2) << endl;
  }
  return 0;
}

