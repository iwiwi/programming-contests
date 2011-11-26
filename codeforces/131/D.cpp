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



int N, s, t;
vector<int> adj[3010];

queue<int> que;
int pot[3010];

bool search(int v, int p) {
  if (v == t) {
    que.push(v);
    pot[v] = 0;
    return true;
  }

  bool r = false;
  rep (i, adj[v].size()) {
    if (adj[v][i] == p) continue;
    r |= search(adj[v][i], v);
  }
  if (r) {
    que.push(v);
    pot[v] = 0;
  }

  return r;
}


int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) adj[i].clear();

    init(N);

    rep (i, N) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      if (find(a, b)) {
        s = a;
        t = b;
      }
      else {
        unite(a, b);
        adj[a].pb(b);
        adj[b].pb(a);
      }
    }

    // printf("%d->%d\n", s, t);

    que = queue<int>();
    memset(pot, -1, sizeof(pot));
    search(s, -1);

    while (!que.empty()) {
      int v = que.front();
      que.pop();
      rep (i, adj[v].size()) {
        int w = adj[v][i];
        if (pot[w] == -1) {
          pot[w] = pot[v] + 1;
          que.push(w);
        }
      }
    }

    rep (i, N) printf("%d%c", pot[i], i + 1 == N ? '\n' : ' ');
  }

  return 0;
}

