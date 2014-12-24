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
#define eb(e) emplace_back(e)
#define mp(a, b) make_pair(a, b)
typedef long long ll;

const int N = 32;
string S[N];

string convert(const string &s, const vector<int> &p) {
  string t = "";
  rep (j, s.length()) t += '0' + p[s[j] - '0'];
  return t;
}

int main() {
  rep (i, N) cin >> S[i];

  vector<int> p(10);
  iota(all(p), 0);
  do {
    if (p[0] != 2) continue;
    if (p[1] != 3) continue;

    rep (i, N) {
      string s = convert(S[i], p);
      if (s.length() > 1 && s[0] == '0') goto dmp;
      ll x = atoll(s.c_str());
      if (x >= (1LL << 32)) goto dmp;
    }

    rep (i, N) {
      cout << convert(S[i], p) << endl;
    }
 dmp:;
  } while (next_permutation(all(p)));
}
