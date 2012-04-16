#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cassert>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define all(c) (c).begin(), (c).end()
#define mp make_pair
#define pb push_back

typedef long long ll;

int N;
vector<int> adj[110];
int A[110], B[110];

map<int, pair<int, int> > mem[110];

pair<int, int> search(int v, int p) {
  if (mem[v].count(p)) return mem[v][p];

  vector<pair<int, pair<int, int> > > vs;
  rep (i, adj[v].size()) {
    int w = adj[v][i];
    if (w == p) continue;
    pair<int, int> p = search(w, v);
    vs.pb(mp(p.first - p.second, p));
  }
  sort(all(vs));
  reverse(all(vs));

  int f = 0, s = 0;
  rep (i, vs.size()) {
    f = max(f, vs[i].second.first + s);
    s += vs[i].second.second;
  }

  f = max(A[v], B[v] + f);
  s = B[v] + s;

  return mem[v][p] = mp(f, s);
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d", &N);
    if (N == 0) return 0;

    rep (i, N) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      B[i] = b + c;
      A[i] = max(a, B[i]);
    }

    rep (i, N) adj[i].clear();
    rep (i, N - 1) {
      int v, w;
      scanf("%d%d", &v, &w);
      --v;
      --w;
      adj[v].pb(w);
      adj[w].pb(v);
    }

    rep (i, N) mem[i].clear();
    pair<int, int> ans = mp(INT_MAX, INT_MAX);
    rep (v, N) ans = min(ans, search(v, -1));
    printf("Case %d: %d\n", ca, ans.first);
  }
}
