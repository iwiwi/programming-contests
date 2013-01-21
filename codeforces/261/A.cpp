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
  int M_, N;
  while (1 == scanf("%d", &M_)) {
    vector<int> Q(M_);
    rep (i, M_) scanf("%d", &Q[i]);

    scanf("%d", &N);
    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);

    int q = *min_element(all(Q));
    sort(all(A));
    reverse(all(A));

    int t = 0, f = 0;
    ll ans = 0;
    rep (i, N) {
      if (f > 0) {
        --f;
      } else {
        ans += A[i];
        ++t;
        if (t == q) {
          t = 0;
          f = 2;
        }
      }
    }
    cout << ans << endl;
  }

  return 0;
}

