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
  ll R1, R2;
  string W1, W2;
  while (cin >> R1 >> R2 >> W1 >> W2) {
    int L1 = W1.length(), L2 = W2.length();

    // Zero?
    rep (i, L2) {
      if (!cpresent(W1, W2[i])) {
        cout << 0 << endl;
        goto done;
      }
    }

    // Solve
    {
      vector<pair<ll, ll> > prv(L1, mp(-1, -1));  // c1, c2
      prv[0] = mp(0, 0);
      ll c1 = 0, c2 = 0;
      int i1 = 0;
      for (;;) {
        rep (i2, L2) {
          for (;;) {
            char t = W1[i1];
            ++i1;
            if (i1 == L1) {
              i1 = 0;
              ++c1;
            }
            if (t == W2[i2]) break;
          }
        }
        if (mp(c1, i1) > mp(R1, 0)) {
          cout << c2 / R2 << endl;
          goto done;
        }
        ++c2;

        if (prv[i1].first == -1) {
          prv[i1] = mp(c1, c2);
        } else {
          ll dc1 = c1 - prv[i1].first;
          ll dc2 = c2 - prv[i1].second;
          ll x = max(0LL, (R1 - c1 - 1) / dc1);
          c1 += dc1 * x;
          c2 += dc2 * x;
        }
      }
    }
 done:;
  }

  return 0;
}

