#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <cassert>
#include <iostream>
#include <gmpxx.h>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

typedef long long ll;

typedef mpz_class bigint;
typedef mpq_class bigrat;

int main() {
  int N;
  cin >> N;
  rep (ca, N) {
    int R, T;
    cin >> R >> T;

    bigrat ans(1, 1);
    vector<bigrat> v(T);
    rep (i, T) {
      bigint a, b;
      cin >> a >> b;
      ans *= bigrat(b - 1, b);// bigrat(a - 1, a);
      v[i] = bigrat(a - 1, a) / bigrat(b - 1, b); // bigrat(b - 1, b) / bigrat(a - 1, a);
    }

    /*
    sort(v.begin(), v.end());
    do {
      bigrat tmp = ans;
      rep (i, R - 1) {
        tmp *= v[i];
      }
      tmp.canonicalize();
      cout << " " << tmp << endl;
      reverse(v.begin() + R - 1, v.end());
    } while (next_permutation(v.begin(), v.end()));
    */

    /*
    bigrat piyo(0);
    rep (hoge, 1000000) {
      bigrat tmp = ans;
      random_shuffle(v.begin(), v.end());
    }
    ans = piyo;
    */

    sort(v.rbegin(), v.rend());
    rep (i, R - 1) {
      ans *= v[i];
      cout << " " << v[i] << endl;
    }

    ans.canonicalize();
    cout << ans << endl;
  }
}
