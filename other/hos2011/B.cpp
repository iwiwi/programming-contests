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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)


const int MAX_V = 100010;

int V;
vector<int> adj[MAX_V], wgh[MAX_V];

int pot[MAX_V];

int dijkstra(int s, int t) {
  multimap<int, int> que;
  fill(pot, pot + V, INT_MAX);
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
  return INT_MAX;
}



int main() {
  int E, D, S, T;
  while (5 == scanf("%d%d%d%d%d", &V, &E, &D, &S, &T)) {
    rep (v, V) {
      adj[v].clear();
      wgh[v].clear();
    }

    rep (v, V - 1) {
      adj[v].pb(v + 1); wgh[v].pb(D);
      adj[v + 1].pb(v); wgh[v + 1].pb(D);
    }

    rep (i, E) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      adj[a].pb(b); wgh[a].pb(c);
      adj[b].pb(a); wgh[b].pb(c);
    }

    printf("%d\n", dijkstra(S, T));
  }

  return 0;
}

