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

int N, M;
int A[100010];
vector<int> adj[100010];
vector<int> rev[100010];

bool asg[100010];
bool usd[100010];

void dfs_asg(int v) {
  if (asg[v]) return;
  asg[v] = true;
  // if (A[v] == 2) return;

  rep (i, adj[v].size()) dfs_asg(adj[v][i]);
}

void dfs_usd(int v) {
  if (usd[v]) return;
  usd[v] = true;
  if (A[v] == 1) return;

  rep (i, rev[v].size()) dfs_usd(rev[v][i]);
}

int main() {
  bool first = true;
  while (2 == scanf("%d%d", &N, &M)) {
    if (first) first = false; else puts("");

    rep (i, N) scanf("%d", &A[i]);

    rep (i, N) adj[i].clear(), rev[i].clear();
    rep (i, M) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a; --b;
      adj[a].pb(b);
      rev[b].pb(a);
    }

    memset(asg, 0, sizeof(asg));
    memset(usd, 0, sizeof(usd));
    rep (v, N) {
      if (A[v] == 1) dfs_asg(v);
      if (A[v] == 2) dfs_usd(v);
    }

    rep (v, N) printf("%d\n", asg[v] && usd[v] ? 1 : 0);
  }

  return 0;
}


