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

typedef long long ll;

int N, A[100010];
vector<int> adj[100010];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }

pair<ll, int> doit(int v, int p) {
  ll mi = ll(1E13) + 100;
  int lc = 1;
  int ch = 0;

  rep(i, adj[v].size()) {
    if (adj[v][i] == p) continue;
    pair<ll, int> r = doit(adj[v][i], v);
    mi = min(mi, r.first);

    lc = lcm(lc, r.second);
    if (lc > mi) lc = mi + 1;

    ++ch;
  }

  if (ch == 0) {  // Leaf
    return make_pair(A[v], 1);
  } else {
    ll x = mi / lc * (ll)lc;
    return mp(x * ch, lc * ch);
  }
}

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", &A[i]);

    rep (i, N) adj[i].clear();
    rep (i, N - 1) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      adj[a].pb(b);
      adj[b].pb(a);
    }

    ll S = 0;
    rep (i, N) S += A[i];

    pair<ll, int> p = doit(0, -1);
    cout << S - p.first << endl;
  }
}
