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
  string S;
  while (cin >> S) {
    string original = S;

    string pfx, sfx;
    while (!S.empty() && S[0] == '_') {
      pfx += "_";
      S = S.substr(1);
    }
    while (!S.empty() && S[S.length() - 1] == '_') {
      sfx += "_";
      S = S.substr(0, S.length() - 1);
    }

    rep (i, S.length()) {
      if (S[i] == '_') {
        if (i + 1 < (int)S.length() && S[i + 1] == '_') goto nazo;
        S[i] = ' ';
      }
    }
    {
      stringstream ss(S);
      vector<string> v;
      for (string s; ss >> s; ) v.pb(s);

      if (v.size() == 0) goto nazo;

      if (v.size() == 1) {
        // Maybe camel
        if (isupper(S[0])) goto nazo;

        vector<string> w(1, "");
        rep (i, S.length()) {
          if (isupper(S[i])) {
            w.pb("");
            S[i] = tolower(S[i]);
          }
          w.back() += S[i];
        }

        cout << pfx << w[0];
        for (int i = 1; i < (int)w.size(); ++i) cout << "_" << w[i];
        cout << sfx << endl;
        goto done;
      } else {
        // Maybe underscore
        rep (i, v.size()) {
          if (!islower(v[i][0])) goto nazo;
          rep (j, v[i].length()) if (isupper(v[i][j])) goto nazo;
        }

        cout << pfx << v[0];
        for (int i = 1; i < (int)v.size(); ++i) cout << (char)toupper(v[i][0]) << v[i].substr(1);
        cout << sfx << endl;
        goto done;
      }
    }

 nazo:
    cout << original << endl;
 done:;
  }

  return 0;
}

