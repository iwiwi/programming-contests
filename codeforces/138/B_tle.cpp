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
  string s;
  while (cin >> s) {
    pair<int, pair<string, string> > ans = mp(-1, mp("", ""));

    sort(all(s));
    string t = s;
    do {
      do {
        int a = atoi(s.c_str()) + atoi(t.c_str());
        int k = 0;
        while (a % 10 == 0) {
          ++k;
          a /= 10;
        }
        ans = max(ans, mp(k, mp(s, t)));
      } while (next_permutation(all(t)));
    } while (next_permutation(all(s)));

    cout << ans.second.first  << endl
         << ans.second.second << endl;
  }

  return 0;
}

