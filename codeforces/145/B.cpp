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

string add47(string s, int C4, int C7) {
  int r4 = C4 - count(all(s), '4');
  int r7 = C7 - count(all(s), '7');
  if (r4 < 0 || r7 < 0) return "";

  rep (i, s.length()) {
    if (s[i] == '4') {
      string t = string(r4, '4');
      s.insert(s.begin() + i, all(t));
      break;
    }
  }

  rep (i, s.length()) {
    int k = s.length() - i - 1;
    if (s[k] == '7') {
      string t = string(r7, '7');
      s.insert(s.begin() + k, all(t));
      break;
    }
  }

  return s;
}

string gen0(int C47, int C74) {
  string s = "4";
  while (C47 > 0) {
    if (s[s.length() - 1] != '4') return "";
    s += '7';
    --C47;

    if (C74 > 0) {
      s += '4';
      --C74;
    }
  }
  if (C74 > 0) return "";

  return s;
}

// 4-start
string gen4(int C4, int C7, int C47, int C74) {
  string s = gen0(C47, C74);
  return add47(s, C4, C7);
}

// 7-start
string gen7(int C4, int C7, int C47, int C74) {
  string s = gen0(C74, C47);
  rep (i, s.length()) s[i] = s[i] == '4' ? '7' : '4';
  return add47(s, C4, C7);
}

const string INF = string(3000000, '9');

int main() {
  int C4, C7, C47, C74;
  while (cin >> C4 >> C7 >> C47 >> C74) {

    string s4 = gen4(C4, C7, C47, C74);
    string s7 = gen7(C4, C7, C47, C74);

    if (s4 == "") s4 = INF;
    if (s7 == "") s7 = INF;
    string s = min(s4, s7);

    if (s == INF) cout << -1 << endl;
    else cout << s << endl;
  }

  return 0;
}

