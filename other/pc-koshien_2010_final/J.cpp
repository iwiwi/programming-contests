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

int N;
vector<int> adj[100010];
vector<int> wgh[100010];

bool leaf[100010];

int saiki(int v, int p) {
  int res = 0;
  rep (i, adj[v].size()) {
    int w = adj[v][i];
    if (w != p && !leaf[w]) {
      res = max(res, wgh[v][i] + saiki(w, v));
    }
  }
  return res;
}

int main() {
  for (;;) {
    scanf("%d", &N);
    if (N == 0) return 0;
    rep (i, N) adj[i].clear(), wgh[i].clear();

    rep (i, N - 1) {
      int a, b, t;
      scanf("%d%d%d", &a, &b, &t);
      --a;
      --b;
      adj[a].pb(b); wgh[a].pb(t);
      adj[b].pb(a); wgh[b].pb(t);
    }

    rep (i, N) leaf[i] = adj[i].size() == 1;
    leaf[0] = false;

    int ans = 0;
    rep (v, N) {
      rep (i, adj[v].size()) {
        int w = adj[v][i];
        if (leaf[v] || leaf[w]) continue;
        ans += wgh[v][i];
      }
    }
    ans -= saiki(0, -1);
    printf("%d\n", ans);
  }

  return 0;
}

