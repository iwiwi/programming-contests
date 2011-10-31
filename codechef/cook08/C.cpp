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
  int T;
  scanf("%d", &T);
  while (T--) {
    ll A, B, C;
    cin >> A >> B >> C;

    ll ma = -1, ans = -1;
    rep (iter, 10010) {
      // printf("%lld %lld\n", A, B);

      ll tmp = A * 100 + B;
      if (tmp > ma) {
        ma = tmp;
        ans = iter;
      }

      while (C > B) {
        if (A == 0) goto done;
        --A;
        B += 100;
      }
      B -= C;
      swap(A, B);

    }

 done:
    cout << ans << endl;
  }

  return 0;
}

