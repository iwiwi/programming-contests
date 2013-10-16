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

int main() {
  ll AN, BN;
  string AS, BS;
  while (cin >> AN >> BN >> AS >> BS) {
    ll AL = AS.length(), BL = BS.length();
    if (AL < BL) {
      swap(AN, BN);
      swap(AS, BS);
      swap(AL, BL);
    }
    // AL >= BL

    vector<vector<int> > aps;
    vector<bool> usd(AL);
    rep (ai, AL) if (!usd[ai]) {
      int aj = ai;
      vector<int> g;
      do {
        usd[aj] = true;
        g.eb(aj);
        aj = (aj + BL) % AL;
      } while (aj != ai);
      aps.eb(g);
    }

    ll score = 0;
    rep (i, aps.size()) {
      vector<int> &g = aps[i];
      sort(all(g));

      ll cnt[256] = {};
      rep (j, g.size()) if (g[j] < BL) ++cnt[int(BS[g[j]])];
      ll c = BN / g.size();
      rep (j, g.size()) score += c * cnt[int(AS[g[j]])];
    }

    cout << AL * AN - score << endl;
  }
}
