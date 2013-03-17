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

const int MAX_LR = 30010;

int L, R;
vector<int> adj[MAX_LR];
bool vis[MAX_LR], usd[MAX_LR];
int lev[MAX_LR + 1], mat[MAX_LR];

bool augment(int l) {
  if (l == L) return true;
  if (vis[l]) return false;
  vis[l] = true;
  rep (i, adj[l].size()) {
    int r = adj[l][i], l2 = mat[r];
    if (lev[l2] > lev[l] && augment(l2)) {
      mat[r] = l;
      return true;
    }
  }
  return false;
}

int bipartite_matching() {
  fill(mat, mat + R, L);
  memset(usd, 0, sizeof(bool) * L);
  bool update;
  do {
    fill(lev, lev + L + 1, -1);
    lev[L] = R;
    queue<int> que;
    rep (l, L) if (!usd[l]) {
      que.push(l);
      lev[l] = 0;
    }
    while (!que.empty()) {
      int l = que.front();
      que.pop();
      rep (i, adj[l].size()) {
        int r = adj[l][i], l2 = mat[r];
        if (lev[l2] < 0) {
          lev[l2] = lev[l] + 1;
          que.push(l2);
        }
      }
    }

    memset(vis, 0, sizeof(bool) * L);
    update = false;
    rep (l, L) if (!usd[l] && augment(l)) usd[l] = update = true;
  } while (update);

  return count(usd, usd + L, true);
}

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    int X[300][3];
    rep (i, N) rep (j, 3) scanf("%d", &X[i][j]);

    map<int, int> id;
    vector<pair<int, int> > es;

    rep (i, N) {
      int t = X[i][0] * X[i][1] * X[i][2];
      rep (j, 3) for (int x = 1; x < X[i][j]; ++x) {
        int a = t / X[i][j] * x;
        int b = t / X[i][j] * (X[i][j] - x);
        id[a] = id[b] = 0;
        es.pb(mp(a, b));
      }
    }

    int V = 0;
    tr (id, ite) ite->second = V++;
    fprintf(stderr, "V=%d\n", V);

    L = R = V;
    rep (i, L) adj[i].clear();
    rep (i, es.size()) adj[id[es[i].first]].pb(id[es[i].second]);

    int m = bipartite_matching();
    printf("%d\n", L + R - m);
  }

  return 0;
}

