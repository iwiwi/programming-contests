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

string S;

template<class T> vector<T> parse(const string &str) {
  stringstream ss(str);
  vector<T> res;
  T t;
  while (ss >> t) res.push_back(t);
  return res;
}

int main() {
  getline(cin, S);

  int N;
  cin >> N;
  vector<string> T(N);
  rep (i, N) cin >> T[i];

  vector<string> ss = parse<string>(S);
  rep (i, ss.size()) {
    rep (j, N) {
      if (ss[i].length() != T[j].length()) goto ng;
      rep (k, T[j].length()) {
        if (T[j][k] != '*' && T[j][k] != ss[i][k]) goto ng;
      }
      goto matched;
   ng:;
    }
    continue;
 matched:
    ss[i] = string(ss[i].length(), '*');
  }

  rep (i, ss.size()) cout << ss[i] << (i + 1 == (int)ss.size() ? '\n' : ' ');

  return 0;
}

