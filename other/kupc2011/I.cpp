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

// MENDOKUSAI NODE BIPARTITE-MATCHING SHIMASU

const int MAX_LR = 3010;

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


int H, W;
int A[1010][1010];

bool solve(vector<vector<int> > &rows) {
  sort(all(rows));
  reverse(all(rows));
  int N = rows.size();
  int M = rows[0].size();

  L = R = N;
  rep (i, N) adj[i].clear();
  
  rep (i, N) {
    for (int j = i + 1; j < N; ++j) {
      rep (k, M) if (rows[i][k] < rows[j][k]) goto ng;
      adj[i].pb(j);

      // rep (k, M) printf("%d ", rows[j][k]); printf(" --- ");rep (k, M) printf("%d ", rows[i][k]); puts("");

      if (false){
      ng:
        if (i == 0) return false;
      }
    }
  }

  int bm = bipartite_matching();
  // printf("bm = %d\n", bm);
  return bm >= N - 2;
}

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    rep (y, H) rep (x, W) scanf("%d", &A[y][x]);

    vector<vector<int> > rows(H), cols(W);
    rep (y, H) rep (x, W) rows[y].pb(A[y][x]);
    rep (x, W) rep (y, H) cols[x].pb(A[y][x]);

    if (solve(rows) && solve(cols)) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
}
