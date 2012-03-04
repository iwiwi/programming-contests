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

const int INF = 1000000000;
const int MAX_N = 210;
const int MAX_T = 7;

int N;
int cost[MAX_N];
vector<int> ter;

int adj[MAX_N][MAX_N];
int prv_adj[MAX_N][MAX_N];

int opt[1 << MAX_T][MAX_N];
pair<bool, int> prv_opt[1 << MAX_T][MAX_N];

vector<int> sol;

void restore_path(int v, int w) {
  if (v == w) return;
  int p = prv_adj[v][w];
  restore_path(v, p);
  sol.pb(p);
}

void restore(int b, int v) {
  if (__builtin_popcount(b) == 1) {
    int t = ter[__builtin_ctz(b)];
    restore_path(t, v);
  } else if (prv_opt[b][v].first) {
    int e = prv_opt[b][v].second;
    restore(e, v);
    restore(b - e, v);
  } else {
    int w = prv_opt[b][v].second;
    restore_path(w, v);
    restore(b, w);
  }
}

int minimum_steiner_tree() {
  int T = ter.size();
  if (T == 0) return 0;

  rep (i, N) adj[i][i] = 0;
  rep (i, N) rep (j, N) prv_adj[i][j] = i;

  rep (k, N) rep (i, N) rep (j, N) {
    int t = adj[i][k] + cost[k] + adj[k][j];
    if (t < adj[i][j]) {
      adj[i][j] = t;
      prv_adj[i][j] = prv_adj[k][j];
    }
  }

  rep (b, 1 << T) rep (v, N) opt[b][v] = b == 0 ? 0 : INF;
  rep (i, T) opt[1 << i][ter[i]] = 0;

  for (int b = 1; b < (1 << T); b++) {
    rep (p, N) {
      int e = b;
      do {
        int t = opt[e][p] + opt[b-e][p];
        if (t < opt[b][p]) {
          opt[b][p] = t;
          prv_opt[b][p] = mp(true, e);
        }
        e = (e - 1) & b;
      } while (e != b);
    }
    rep (v, N) rep (w, N) {
      int t = opt[b][w] + cost[w] + adj[w][v];
      if (t < opt[b][v]) {
        opt[b][v] = t;
        prv_opt[b][v] = mp(false, w);
      }
    }
  }

  sol.pb(ter[0]);
  restore((1 << T) - 1, ter[0]);
  return cost[ter[0]] + opt[(1 << T) - 1][ter[0]];
}



const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int H, W, K;
int fld[110][110];

int vid(int x, int y) {
  return y * W + x;
}

int main() {
  for (; 3 == scanf("%d%d%d", &H, &W, &K); ) {
    rep (y, H) rep (x, W) {
      scanf("%d", &fld[y][x]);
      cost[vid(x, y)] = fld[y][x];
    }

    ter.clear();
    rep (k, K) {
      int y, x;
      scanf("%d%d", &y, &x);
      --y; --x;
      ter.pb(vid(x, y));
      // printf("TER %d\n",ter.back());
    }

    N = W * H;
    rep (i, N) rep (j, N) adj[i][j] = i == j ? 0 : INF;

    rep (y, H) rep (x, W) {
      rep (d, 4) {
        int tx = x + dx[d];
        int ty = y + dy[d];
        if (tx < 0 || W <= tx || ty < 0 || H <= ty) continue;
        adj[vid(x, y)][vid(tx, ty)] = 0;
      }
    }

    sol.clear();
    printf("%d\n", minimum_steiner_tree());

    rep (y, H) {
      char buf[110] = {};
      rep (x, W) {
        int c = count(all(sol), vid(x, y));
        assert(c < 2);
        if (c) buf[x] = 'X';
        else buf[x] = '.';
      }
      puts(buf);
    }
  }

  return 0;
}

