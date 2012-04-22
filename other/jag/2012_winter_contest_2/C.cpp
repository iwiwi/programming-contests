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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

#define F first
#define S second

typedef long long ll;

int N, M;
vector<int> adj[20];

pair<int, int> pos(int i) {
  int s = 0;
  for (int r = 0; ; ++r) {
    if (i < s + (r + 1)) return mp(r, i - s);
    s += r + 1;
  }
}

void add_pos(int i, int j, pair<int, int> p) {
  if (0 <= p.F && p.F < N && 0 <= p.S && p.S <= p.F) {
    adj[i].pb(j);
  }
}

void init(int n) {
  N = n;
  M = n * (n + 1) / 2;
  rep (i, M) {
    adj[i].clear();
    pair<int, int> p = pos(i);
    add_pos(i, i - 1, mp(p.F, p.S - 1));
    add_pos(i, i + 1, mp(p.F, p.S + 1));
    add_pos(i, i - p.F, mp(p.F - 1, p.S));
    add_pos(i, i + (p.F + 1), mp(p.F + 1, p.S));
  }
}


ll edit(ll x, int i, ll v) {
  return (x >> ((i + 1) * 4)) << ((i + 1) * 4)
      | (v << (i * 4))
      | (x & ((1LL << (i * 4)) - 1));
}

ll get(ll x, int i) {
  return (x >> (i * 4)) & 0xF;
}

int fld[10][10];
pair<ll, int> enc() {
  int ord[20], k = 0, z = -1;
  rep (i, N) rep (j, i + 1) {
    ord[k++] = fld[N - 1 - i + j][j];
    // printf("(%d, %d) = %d\n", N - 1 - i + j, j, fld[N - 1 - i + j][j]);
  }

  ll e = 0;
  rep (i, M) {
    int a = ord[i] - 1;
    // printf(" a = %d\n", a);
    e = edit(e, i, a);
    if (a == 0) z = i;
  }
  return mp(e, z);
}



map<ll, int> rev[10];


int main() {
  for (int n = 1; n <= 5; ++n) {
    init(n);
    int d_lim = n == 5 ? 25 : 0;
    // rep (i, M) { printf("%d:", i); rep (j, adj[i].size()) printf(" %d", adj[i][j]); puts(""); }

    int k = 1;
    rep (i, n) rep (j, i + 1) fld[i][j] = k++;
    ll s = enc().first;
    int z = enc().second;
    // rep (i, M) printf("%lld ", get(s, i)); puts("");

    queue<pair<ll, pair<int, int> > > que;
    que.push(mp(s, mp(z, 0)));
    rev[n][s] = 0;
    while (!que.empty()) {
      ll s = que.front().first;
      int z = que.front().second.first;
      int d = que.front().second.second;
      que.pop();

      // if (n == 2) { rep (i, M) { if (pos(i).S == 0) puts(""); printf("%2lld ", get(s, i)); } printf("\n^^ (%d) ^^\n", d); }

      if (d >= d_lim) break;

      rep (i, adj[z].size()) {
        int y = adj[z][i];
        int v = get(s, y);
        ll ts = edit(edit(s, z, v), y, 0);
        if (rev[n].insert(mp(ts, d + 1)).second == false) continue;
        que.push(mp(ts, mp(y, d + 1)));
      }
    }

    // printf("%d: %d\n", n, (int)rev[n].size());
  }

  for (int ca = 1; ; ++ca) {
    int n;
    scanf("%d", &n);
    if (n == 0) return 0;
    init(n);

    rep (i, N) rep (j, i + 1) scanf("%d", &fld[i][j]);
    ll s = enc().first;
    int z = enc().second;

    int ans = INT_MAX;

    queue<pair<ll, pair<int, int> > > que;
    que.push(mp(s, mp(z, 0)));
    set<ll> vis;
    while (!que.empty()) {
      ll s = que.front().first;
      int z = que.front().second.first;
      int d = que.front().second.second;
      que.pop();

      if (rev[n].count(s)) {
        ans = d + rev[n][s];
        // fprintf(stderr, "%d + %d\n", d, rev[n][s]);
        break;
      }

      // rep (i, M) { if (pos(i).S == 0) puts(""); printf("%2lld ", get(s, i)); } printf("\n^^ (%d) ^^\n", d);

      rep (i, adj[z].size()) {
        int y = adj[z][i];
        int v = get(s, y);
        ll ts = edit(edit(s, z, v), y, 0);
        if (vis.count(ts)) continue;
        que.push(mp(ts, mp(y, d + 1)));
        vis.insert(ts);
      }
    }
    printf("Case %d: %d\n", ca, ans);
    // break;
  }

  return 0;
}

