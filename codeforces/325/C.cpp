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
const ll PIE = 314000000;

namespace SCC {
const int MAX_N = 100010;

int N;
vector<int> adj[MAX_N], rev[MAX_N];

bool vis[MAX_N];
int ord[MAX_N], num, id[MAX_N];

void dfs1(int v) {
  if (vis[v]) return;
  vis[v] = true;
  for (int i = 0; i < (int)adj[v].size(); i++) dfs1(adj[v][i]);
  ord[num++] = v;
}

void dfs2(int v) {
  if (vis[v]) return;
  vis[v] = true; id[v] = num;
  for (int i = 0; i < (int)rev[v].size(); i++) dfs2(rev[v][i]);
}

void scc() {
  memset(vis, 0, sizeof(vis)); num = 0;
  for (int i = 0; i < N; i++) dfs1(i);
  memset(vis, 0, sizeof(vis)); num = 0;
  for (int i = N-1; i >= 0; i--) if (!vis[ord[i]]) dfs2(ord[i]), num++;
}
}

int R, M;
vector<int> M2Ro[100010];
vector<int> M2Ri[100010];
int R2M[100010];
vector<int> R2L[100010];
bool R2NG[100010];

int ind[100010], scr[100010];
int ans_min[100010];

vector<int> scc2M[100010];
int ans_max[100010];

int main() {
  while (2 == scanf("%d%d", &R, &M)) {
    rep (m, M) {
      M2Ro[m].clear();
      M2Ri[m].clear();
    }
    rep (r, R) {
      int l;
      scanf("%d%d", &R2M[r], &l);
      --R2M[r];
      M2Ro[R2M[r]].pb(r);

      R2L[r].resize(l);
      rep (i, l) {
        scanf("%d", &R2L[r][i]);
        --R2L[r][i];
        if (R2L[r][i] != -2) M2Ri[R2L[r][i]].pb(r);
      }
    }

    //
    // Dijkstra
    //
    multimap<int, int> que;
    rep (r, R) {
      scr[r] = ind[r] = 0;
      rep (i, R2L[r].size()) {
        if (R2L[r][i] == -2) ++scr[r];
        else ++ind[r];
      }
      if (ind[r] == 0) que.insert(mp(scr[r], R2M[r]));
    }
    memset(ans_min, -1, sizeof(ans_min));

    while (!que.empty()) {
      int s = que.begin()->first;
      int m = que.begin()->second;
      que.erase(que.begin());
      if (ans_min[m] != -1) continue;

      ans_min[m] = s;

      rep (i, M2Ri[m].size()) {
        int r = M2Ri[m][i];
        scr[r] = min((int)PIE, scr[r] + s);
        if (--ind[r] == 0) que.insert(mp(scr[r], R2M[r]));
      }
    }
    rep (r, R) {
      R2NG[r] = false;
      rep (i, R2L[r].size()) R2NG[r] |= R2L[r][i] != -2 && ans_min[R2L[r][i]] == -1;
    }

    //
    // SCC
    //
    SCC::N = M;
    rep (m, M) {
      SCC::adj[m].clear();
      SCC::rev[m].clear();
      ans_max[m] = -1;
    }
    rep (r, R) {
      int m1 = R2M[r];
      if (ans_min[m1] == -1 || R2NG[r]) continue;
      bool self_link = false;
      rep (i, R2L[r].size()) {
        int m2 = R2L[r][i];
        if (m2 == -2) {
          continue;
        } else if (m2 == m1) {
          self_link = true;
        } else {
          SCC::adj[m1].pb(m2);
          SCC::rev[m2].pb(m1);
        }
      }
      if (self_link) ans_max[m1] = -2;
    }
    SCC::scc();

    //
    // DP
    //
    rep (scc, SCC::num) scc2M[scc].clear();
    rep (m, M) if (ans_min[m] != -1) scc2M[SCC::id[m]].pb(m);
    for (int scc = SCC::num - 1; scc >= 0; --scc) {
      const vector<int> &ms = scc2M[scc];
      rep (i, ms.size()) {
        int m = ms[i];
        if (ans_max[m] != -1) continue;
        if (ms.size() >= 2) {
          ans_max[m] = -2;
        } else {
          rep (j, M2Ro[m].size()) {
            int r = M2Ro[m][j];
            if (R2NG[r]) continue;
            ll s = 0;
            bool inf = false;
            rep (k, R2L[r].size()) {
              int m2 = R2L[r][k];
              if (m2 == -2) ++s;
              else if (ans_max[m2] == -2) inf = true;
              else s += ans_max[m2];
            }
            if (inf) {
              ans_max[m] = -2;
              break;
            } else {
              ans_max[m] = max(ans_max[m], (int)min(s, PIE));
            }
          }
        }
      }
    }

    //
    // Output
    //
    rep (m, M) printf("%d %d\n", ans_min[m], (ans_min[m] == -1 ? -1 : ans_max[m]));
  }

  return 0;
}
