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


/*
  Heroes collect artifacts completely independently. I. e. each hero can use only his own basic artifacts during the composing the
complex ones.
*/

int main() {
  string line;

  int K, N, M, Q;
  getline(cin, line);
  sscanf(line.c_str(), "%d%d%d%d", &K, &N, &M, &Q);

  rep (i, N) getline(cin, line);

  map<string, vector<pair<string, int> > > comp;
  rep (i, M) {
    getline(cin, line);
    rep (i, line.length()) if (!isalnum(line[i])) line[i] = ' ';
    stringstream ss(line);

    string name;
    ss >> name;

    string t;
    int k;
    while (ss >> t >> k) comp[name].pb(mp(t, k));
  }

  map<string, int> players[110];
  rep (i, Q) {
    int p;
    string s;
    cin >> p >> s;
    --p;
    ++players[p][s];

    for (;;) {
      bool up = false;
      tr (comp, ite) {
        vector<pair<string, int> > &v = ite->second;
        rep (i, v.size()) {
          if (players[p][v[i].first] < v[i].second) goto ng;
        }
        rep (i, v.size()) {
          players[p][v[i].first] -= v[i].second;
        }
        ++players[p][ite->first];
        up = true;
       ng:;
      }
      if (!up) break;
    }
  }

  rep (p, K) {
    int cnt = 0;
    tr (players[p], ite) if (ite->second > 0) ++cnt;
    printf("%d\n", cnt);
    tr (players[p], ite) if (ite->second > 0) printf("%s %d\n", ite->first.c_str(), ite->second);
  }

  return 0;
}

