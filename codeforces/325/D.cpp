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

const int MAX_N = 1000000;

int par[MAX_N], rank[MAX_N];

void init(int n) {
  for (int i = 0; i < n; i++) {
    par[i] = i;
    rank[i] = 0;
  }
}

int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}

void unite(int x, int y) {
  x = root(x);
  y = root(y);
  if (x == y) return;

  if (rank[x] < rank[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rank[x] == rank[y]) rank[x]++;
  }
}

bool find(int x, int y) {
  return root(x) == root(y);
}

int H, W, N, W2;
int Y[1000010], X[1000010];
int K;

int id[3010][6010];

const int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int main() {
  scanf("%d%d%d", &H, &W, &N);
  W2 = W * 2;

  memset(id, -1, sizeof(id));
  rep (i, N) {
    scanf("%d%d", &Y[i], &X[i]);
    --Y[i];
    --X[i];
  }
  init(N * 2);

  int ans = 0;
  rep (i, N) {
    if (W == 1) continue;

    int x = X[i], y = Y[i];

    // Test
    rep (d1, 8) rep (d2, 8) {
      int tx1 = (x     + dx[d1] + W2) % W2, ty1 = y + dy[d1];
      int tx2 = (x + W + dx[d2] + W2) % W2, ty2 = y + dy[d2];
      if (min(ty1, ty2) < 0 || H <= max(ty1, ty2)) continue;
      int k1 = id[ty1][tx1];
      int k2 = id[ty2][tx2];
      if (k1 != -1 && k2 != -1 && find(k1, k2)) goto dmp;
    }

    // Place
    rep (z, 2) {
      id[y][x] = i + z * N;
      rep (d, 8) {
        int tx = (x + dx[d] + W2) % W2, ty = y + dy[d];
        if (ty < 0 || H <= ty) continue;
        int k = id[ty][tx];
        if (k != -1) unite(id[y][x], k);
      }
      x += W;
    }
    ++ans;
    continue;
 dmp:;
  }
  printf("%d\n", ans);
  return 0;
}

