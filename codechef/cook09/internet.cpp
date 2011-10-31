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
  int N, Q;
  cin >> N >> Q;

  map<string, string> ma;
  rep (i, N) {
    string a, b;
    cin >> a >> b;
    ma[a] = b;
  }

  rep (i, Q) {
    string a;
    cin >> a;
    string::size_type p = a.rfind('.');

    if (p == string::npos) {
      cout << "unknown" << endl;
    }
    else {
      string ext = a.substr(p + 1);
      if (ma.count(ext)) {
        cout << ma[ext] << endl;
      } else {
        cout << "unknown" << endl;
      }
    }
  }

  return 0;
}

