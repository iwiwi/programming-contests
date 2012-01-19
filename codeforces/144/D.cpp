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

const int INF = 1E9;
const int MAX_V = 100010;

int V;
vector<int> adj[MAX_V], wgh[MAX_V];

int pot[MAX_V];

int dijkstra(int s, int t = -1) {
  multimap<int, int> que;
  fill(pot, pot + V, INF);
  que.insert(mp(0, s));
  pot[s] = 0;
  while (!que.empty()) {
    int c = que.begin()->first;
    int v = que.begin()->second;
    que.erase(que.begin());
    if (c > pot[v]) continue;
    if (v == t) return c;

    rep (i, adj[v].size()) {
      int w = adj[v][i];
      int d = c + wgh[v][i];
      if (d < pot[w]) {
        que.insert(mp(d, w));
        pot[w] = d;
      }
    }
  }
  return INF;
}

int A[100010], B[100010], C[100010];

int main() {
  int N, M, S;
  while (3 == scanf("%d%d%d", &N, &M, &S)) {
    --S;
    rep (v, N) adj[v].clear(), wgh[v].clear();

    rep (i, M) {
      int v, w, d;
      scanf("%d%d%d", &v, &w, &d);
      A[i] = --v;
      B[i] = --w;
      C[i] = d;

      adj[v].pb(w); wgh[v].pb(d);
      adj[w].pb(v); wgh[w].pb(d);
    }
    int L;
    scanf("%d", &L);

    V = N;
    dijkstra(S);

    int ans = 0;
    rep (v, N) {
      // printf(" %d: %d\n", v + 1, pot[v]);
      if (pot[v] == L) ++ans;
    }

    rep (i, M) {
      int v = A[i], w = B[i], d = C[i];

      double x = pot[v] + (d + pot[w] - pot[v]) / 2.0;
      // printf(" %d %d %d: %lf -> %d\n", v + 1, w + 1, d, x, ans);
      if (x == L && pot[v] != L && pot[w] != L) ++ans;
      else {
        if (pot[v] < L && L < x) ++ans;
        if (pot[w] < L && L < x) ++ans;
      }
    }

    printf("%d\n", ans);
  }

  return 0;
}

