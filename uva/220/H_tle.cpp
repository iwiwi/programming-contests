#include <cstdio>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair
#define pb push_back

int A[210][210];
int F[210][210];

int V, S, T;
int lev[210], done[210];
int adj[210][210];

bool levelize() {
  memset(lev, -1, sizeof(lev));
  queue<int> que;
  lev[S] = 0;
  que.push(S);
  while (!que.empty()) {
    int v = que.front(); que.pop();
    rep (w, V) if (adj[v][w] > 0) {
      if (lev[w] != -1) continue;
      lev[w] = lev[v] + 1;
      que.push(w);
    }
  }
  return lev[T] != -1;
}

int augment(int v, int f) {
  if (v == T || !f) return f;
  for (; done[v] < V; ++done[v]) {
    int w = done[v];
    if (lev[w] <= lev[v]) continue;
    int t = augment(w, min(f, adj[v][w]));
    if (t > 0) {
      adj[v][w] -= t;
      adj[w][v] += t;
      return t;
    }
  }
  return 0;
}

int max_flow() {
  int f = 0, t;
  while (levelize()) {
    memset(done, 0, sizeof(done));
    while (0 < (t = augment(S, INT_MAX))) f += t;
  }
  return f;
}


int main() {
  int cases;
  scanf("%d", &cases);
  rep (ca, cases) {
    int v;
    scanf("%d", &v);
    rep (i, v) rep (j, v) scanf("%d", &A[i][j]);

    V = v;
    for (S = 0; S < v; ++S) {
      for (T = 0; T < S; ++T) {
        rep (i, v) rep (j, v) adj[i][j] = A[i][j];
        F[S][T] = F[T][S] = max_flow();
      }
    }

    printf("Case %d:\n", ca + 1);
    rep (i, v) rep (j, v) printf("%d%c", F[i][j], j + 1 == v ? '\n' : ' ');
  }
}
