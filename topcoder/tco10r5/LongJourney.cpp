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
#include <numeric>
using namespace std;
 
#define all(c) (c).begin(), (c).end() 
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end()) 
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

ll INF = 987654321987654321LL;


vector<string> split(string s, const string &t) {
  vector<string> v;
  for (string::size_type p = s.find(t); p != s.npos; p = s.find(t)) {
    v.push_back(s.substr(0, p));
    s = s.substr(p + t.size());
  }
  v.push_back(s);
  return v;
}


struct LongJourney {
  long long minimumCost(vector <int> fuelPrices, int fuelTank, vector <string> roads) {
    int N = fuelPrices.size();
    ll mat[60][60];

    rep (i, N) rep (j, N) mat[i][j] = INF;
    rep (i, N) mat[i][i] = 0;

    vector<string> tmp = split(accumulate(all(roads), string()), string(" "));
    rep (i, tmp.size()) {
      int a, b, c;
      sscanf(tmp[i].c_str(), "%d,%d,%d", &a, &b, &c);
      mat[a][b] = mat[b][a] = min(mat[a][b], (ll)c);
    }

    rep (k, N) rep (i, N) rep (j, N) mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);

    ll pot[60][60];
    multimap<ll, pair<int, int> > que;
    rep (i, N) rep (j, N + 1) pot[i][j] = INF;
    pot[0][N] = 0;
    que.insert(mp(0, mp(0, N)));
    
    while (!que.empty()) {
      ll c = que.begin()->first;
      int v = que.begin()->second.first;
      int w = que.begin()->second.second;
      que.erase(que.begin());
      if (c > pot[v][w]) continue;

      if (v == 1 && w == N) return c;

      ll f;
      if (w == N) f = 0;
      else f = fuelTank - mat[w][v];

      // girigiri
      rep (tv, N) if (mat[v][tv] <= fuelTank) {
        ll reqf = mat[v][tv];
        if (f > reqf) continue;
        int tw = N;
        ll tc = c + fuelPrices[v] * (reqf - f);
        if (tc < pot[tv][tw]) {
          pot[tv][tw] = tc;
          que.insert(mp(tc, mp(tv, tw)));
        }
      }
      
      // mantan
      rep (tv, N) if (mat[v][tv] <= fuelTank) {
        int tw = v;
        ll tc = c + fuelPrices[v] * (fuelTank - f);
        if (tc < pot[tv][tw]) {
          pot[tv][tw] = tc;
          que.insert(mp(tc, mp(tv, tw)));
        }
      }
    }

    return -1;
  }

  

};





// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
