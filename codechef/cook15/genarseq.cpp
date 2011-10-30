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

#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

const int L = 3000000;

int main() {
  int T;
  cin >> T;
  while (T--) {
    ll A, B;
    int N;
    cin >> A >> B >> N;

    bitset<L> ng;

    vector<int> x(N);

    // set<ll> ng;
    int last = 0;
    rep (i, N) {
      int k;
      // for (k = last + 1; ng.count(k) > 0; ++k);
      for (k = last + 1; ng[k]; ++k);

      // printf("%lld\n", k);
      x[i] = k;
      rep (j, i + 1) {
        ll x0 = x[j], x1 = x[i];
        rep (iter, 2) {
          ll t = A * x0 - B * x1;
          if (k < t && k < L) ng[t] = true;
          swap(x0, x1);
        }

        // ng.insert(A * x[j] - B * x[i]);
        // ng.insert(A * x[i] - B * x[j]);
        // printf(" %lld %lld\n", A * x[j] - B * x[i], B * x[j] - A * x[i]);
      }
      last = k;
    }

    rep (i, N) {
      if (i) printf(" %d", x[i]);
      else printf("%d", x[i]);
    }
    puts("");
  }

  return 0;
}

