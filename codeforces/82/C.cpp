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

int N, A[5010];
vector<int> adj[5010], wgh[5010];

int par[5010];
int cap[5010][5010];

void search(int v, int p, int c) {
  par[v] = p;
  rep (t, N + 5) cap[t][v] = c;
  rep (i, adj[v].size()) {
    if (adj[v][i] == p) continue;
    search(adj[v][i], v, wgh[v][i]);
  }
}

int ans[5010];

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", &A[i]);
    rep (i, N - 1) {
      int v, u, c;
      scanf("%d%d%d", &v, &u, &c);
      --v;
      --u;
      adj[u].pb(v); wgh[u].pb(c);
      adj[v].pb(u); wgh[v].pb(c);
    }
    search(0, -1, 0);

    vector<pair<int, int> > ord(N);
    rep (i, N) ord[i] = mp(A[i], i);
    sort(all(ord));
    rep (i, N) {
      int k = ord[i].second;
      int v = k;
      int t = 0;
      while (v != 0) {
        while (cap[t][v] == 0) ++t;
        --cap[t][v];
        v = par[v];
        ++t;
      }
      ans[k] = t;
    }

    rep (i, N) printf("%d%c", ans[i], i == N - 1 ? '\n' : ' ');
  }

  return 0;
}

