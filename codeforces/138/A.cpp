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




int main() {
  int N, K;
  while (cin >> N >> K) {
    string res = "aaaa";

    rep (i, N) {
      vector<string> ss;

      rep (j, 4) {
        string s;
        cin >> s;

        int k = 0;
        for (int p = s.length() - 1; p >= 0; --p) {
          if (strchr("aeiou", s[p]) != NULL) ++k;
          if (k >= K) {
            ss.pb(s.substr(p));
            break;
          }
        }
      }

      // rep (j, ss.size()) cout << ss[j] << endl;

      string tmp;
      if (ss.size() < 4) {
        tmp = "NO";
      } else if (ss[0] == ss[1] && ss[1] == ss[2] && ss[2] == ss[3]) {
        tmp = "aaaa";
      } else if (ss[0] == ss[1] && ss[2] == ss[3]) {
        tmp = "aabb";
      } else if (ss[0] == ss[2] && ss[1] == ss[3]) {
        tmp = "abab";
      } else if (ss[0] == ss[3] && ss[1] == ss[2]) {
        tmp = "abba";
      } else {
        tmp = "NO";
      }

      if (tmp == "aaaa") continue;

      if (res == "aaaa") res = tmp;
      else if (res == tmp); // OK
      else res = "NO";  // NG
    }

    cout << res << endl;
  }

  return 0;
}

