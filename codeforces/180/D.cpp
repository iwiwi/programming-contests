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

string gen(int *cnt) {
  string res = "";
  for (int c = 'a'; c <= 'z'; ++c) rep (i, cnt[c]) res += char(c);
  return res;
}

int main() {
  string S, T;
  while (cin >> S >> T) {
    int N = S.length();
    T.resize(N, '0');

    // cout << S << endl; cout << T << endl;

    int cnt[256] = {};
    for (int c = 'a'; c <= 'z'; ++c) cnt[c] = count(all(S), c);

    string res = "";
    rep (i, N) {
      int c = T[i];
      if (cnt[c] > 0) {
        --cnt[c];
        string t = gen(cnt);
        reverse(all(t));

        if (t > T.substr(i + 1)) {
          // cout << t << " > " << T.substr(i + 1) << endl;
          res += char(c);
          continue;
        } else {
          ++cnt[c];
        }
      }

      // oh...
      for (++c; c <= 'z'; ++c) {
        if (cnt[c] > 0) {
          res += char(c);
          --cnt[c];
          res += gen(cnt);
          goto done;
        }
      }

      // ohhhhhh
      // fprintf(stderr, "orz: i=%d\n", i);
      res = "-1";
      goto done;
    }
 done:;
    cout << res << endl;
  }

  return 0;
}

