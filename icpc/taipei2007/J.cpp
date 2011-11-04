#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <cstring>
#include <climits>
#include <sstream>
#include <stack>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<pii> vpii;

string readline() {
  string line;
  getline(cin, line);
  return line;
}

const ll MAX = ll(1) << 35;


void purify(vpii &v) {
  sort(v.begin(), v.end());
  int k = 0;
  rep (i, v.size()) {
    // printf(" PURIFY %d %d\n", v[i].F, v[i].S);
    if (v[i].first * ll(v[i].second) >= MAX) continue;
    if (k > 0 && v[k - 1].second <= v[i].second) continue;
    v[k++] = v[i];
  }
  v.resize(k);
}

void doit(const vpii &v1, const vpii &v2, vpii &res) {
  int n1 = v1.size(), n2 = v2.size();
  int jF = 0, jS = n2 - 1;
  rep (i, n1) {
    while (jF + 1 < n2 && v2[jF + 1].F <= v1[i].F) ++jF;
    while (jS - 1 >= 0 && v2[jS - 1].S <= v1[i].S) --jS;

    res.pb(mp(max(v1[i].F, v2[jF].F), v1[i].S + v2[jF].S));
    res.pb(mp(v1[i].F + v2[jS].F,     max(v1[i].S, v2[jS].S)));
  }
}

int main() {
  int T = atoi(readline().c_str());

  rep (ca, T) {
    int N = atoi(readline().c_str());
    vpii K[2010];

    rep (i, N) {
      K[i].clear();
      stringstream ss(readline());
      for (int a, b; ss >> a >> b; ) K[i].pb(mp(a, b));
      purify(K[i]);
    }

    stringstream ss(readline());
    vector<int> A;
    for (int a; ss >> a; ) A.pb(a);

    vector<vpii> stk;
    rep (i, A.size()) {
      if (A[i] == 0) {
        const vpii &v1 = stk[stk.size() - 2];
        const vpii &v2 = stk[stk.size() - 1];

        // rep (i, v1.size()) printf(" (%lld, %lld)", v1[i].F, v1[i].S); puts("");
        // rep (i, v2.size()) printf(" (%lld, %lld)", v2[i].F, v2[i].S); puts("");
        // puts("");

        vpii res;
        doit(v1, v2, res);
        doit(v2, v1, res);
        purify(res);

        stk.pop_back();
        stk.pop_back();
        stk.push_back(res);
      } else {
        stk.push_back(K[A[i] - 1]);
      }
    }

    ll ans = MAX;
    const vpii &v = stk.back();
    rep (i, v.size()) {
      // printf("%d %d\n", v[i].F, v[i].S);
      ans = min(ans, v[i].F * ll(v[i].S));
    }
    cout << ans << endl;
  }

  return 0;
}
