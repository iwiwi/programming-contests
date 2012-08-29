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
  const char *JQKA = "JQKA";

  string S;
  while (cin >> S) {
    vector<pair<pair<char, int>, string> > C;
    int i = 0;
    while (i < int(S.length())) {
      string s = S.substr(i, 2);
      char c = S[i++];
      int n;
      if (!isdigit(S[i])) n = 11 + (strchr(JQKA, S[i++]) - JQKA);
      else {
        if (isdigit(S[i + 1])) { n = 10;         s += S[i + 1]; i += 2;}
        else                   { n = S[i] - '0';                i += 1; }
      }
      C.pb(mp(mp(c, n), s));
    }

    const char *SHDC = "SHDC";
    vector<string> ans(100000, "");
    rep (iter, 4) {
      char c = SHDC[iter];
      set<int> s;
      rep (i, 5) s.insert(10 + i);

      vector<string> tmp;
      rep (i, C.size()) {
        if (C[i].first.first == c && s.count(C[i].first.second)) {
          s.erase(C[i].first.second);
        }
        else {
          tmp.pb(C[i].second);
        }

        if (s.empty()) {
          if (tmp.size() < ans.size()) ans = tmp;
        }
      }
    }
    if (ans.empty()) puts("0");
    else {
      rep (i, ans.size()) printf("%s", ans[i].c_str());
      puts("");
    }
  }

  return 0;
}

