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

set<string> cities;
map<pair<string, string>, int> edges;

int main() {
  int N;
  cin >> N;
  rep (i, N) {
    string s;
    cin >> s;
    cities.insert(s);
  }

  int M;
  cin >> M;
  rep (i, M) {
    string s, t;
    int c;
    cin >> s >> t >> c;
    edges.insert(mp(mp(s, t), c));
  }

  int T;
  scanf("%d", &T);
  rep (cases, T) {
    int K;
    cin >> K;

    vector<string> route(K);
    rep (i, K) cin >> route[i];

    set<string> visited;
    string prev;
    int len = 0;
    rep (i, K) {
      string s = route[i];

      if (!cities.count(s)) goto ng;
      if (i > 0 && !edges.count(mp(prev, s))) goto ng;
      if (visited.count(s)) goto ng;
      if (i > 0 && prev == s) goto ng;

      len += edges[mp(prev, s)];
      visited.insert(s);
      prev = s;
    }

    printf("%d\n", len);
    continue;
 ng:
    puts("ERROR");
  }

  return 0;
}

