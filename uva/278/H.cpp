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

const int B = 100;

int N, M;
int T[200010], X[200010], Y[200010], C[200010];

int par[50010], col[50010];
int act[50010];

int spar[50010], scol[50010], sdis[50010];

void search(int v) {
  if (spar[v] != -1) return;
  if (par[v] == -1) return;

  int p = par[v];
  if (act[p]) {
    spar[v] = p;
    scol[v] = col[v];
    sdis[v] = 1;
  } else {
    search(p);
    spar[v] = spar[p];
    scol[v] = scol[p] | col[v];
    sdis[v] = sdis[p] + 1;
  }
}

bool is_reachable(int x, int y) {
  int v = x;
  while (v != y && v != -1) {
    search(v);
    v = spar[v];
  }
  return v == y;
}

void do2(int x, int y, int c) {
  int v = x;
  while (v != y) {
    scol[v] = c;
    v = spar[v];
  }
}

int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    rep (i, N) {
      scanf("%d", &par[i]);
      --par[i];
    }
    rep (i, N) {
      scanf("%d", &col[i]);
      col[i] = 1 << (col[i] - 1);
    }

    rep (i, M) {
      scanf("%d%d%d", T + i, X + i, Y + i);
      --X[i];
      --Y[i];
      if (T[i] == 1) {
        scanf("%d", C + i);
        C[i] = 1 << (C[i] - 1);
      }
    }

    for (int b = 0; b < M; ++b) {
      int e = min(M, b + B);  // [b, e)
      for (int i = b; i < e; ++i) ++act[X[i]], ++act[Y[i]];

      memset(spar, -1, sizeof(spar));
      for (int i = b; i < e; ++i) {
        int x = X[i], y = Y[i];
        if (T[i] == 1) {
          if (par[x] == y) continue;
          par[x] = y;
          col[x] = C[i];

          spar[x] = -1;
        }
        else if (T[i] == 2) {
          if (is_reachable(x, y)) do2(x, y, C[i]);
          else if (is_reachable(y, x)) do2(y, x, C[i]);
        }
        else {
          if (is_reachable(x, y)) do3(x, y);
          else if (is_reachable(
        }
      }

      for (int i = b; i < e; ++i) --act[X[i]], --act[Y[i]];
    }
  }

  return 0;
}

