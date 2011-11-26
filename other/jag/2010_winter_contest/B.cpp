#include <cstdio>
#include <climits>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; i++)


const int MAX_V = 1010;

struct e_t { int to, cap, rev; };


int V, S, T;
vector<e_t> adj[MAX_V];

int lev[MAX_V], done[MAX_V];

void add_edge(int i, int j, int c) {
  adj[i].push_back((e_t){j, c, adj[j].size()});
  adj[j].push_back((e_t){i, 0, adj[i].size() - 1});
}

bool levelize() {
  memset(lev, -1, sizeof(lev));
  queue<int> que;
  lev[S] = 0;
  que.push(S);
  while (!que.empty()) {
    int v = que.front();
    que.pop();
    
    rep (i, adj[v].size()) {
      e_t &e = adj[v][i];
      if (e.cap <= 0 || lev[e.to] != -1) continue;
      que.push(e.to);
      lev[e.to] = lev[v] + 1;
    }
  }
  return lev[T] != -1;
}

int augment(int v, int f) {
  if (v == T || f == 0) return f;
  for (; done[v] < (int)adj[v].size(); done[v]++) {
    e_t &e = adj[v][done[v]];
    if (lev[e.to] <= lev[v]) continue;
    int t = augment(e.to, min(f, e.cap));
    if (t > 0) {
      e.cap -= t;
      adj[e.to][e.rev].cap += t;
      return t;
    }
  }
  return 0;
}

int max_flow() {
  int tot = 0, f;
  while (levelize()) {
    memset(done, 0, sizeof(done));
    while (0 < (f = augment(S, INT_MAX))) tot += f;
  }
  return tot;
}


int main() {
  int N, M;
  scanf("%d%d", &N, &M);

  V = N + M + 3;
  S = N + M + 1;
  T = N + M + 2;
  
  rep (i, N) add_edge(S, i, 1);
  rep (i, M) add_edge(N + i, T, 1);

  rep (i, N) {
    int k, a;
    scanf("%d", &k);
    rep (j, k) {
      scanf("%d", &a);
      a--;
      // printf(" %d-%d\n", i, N + a);
      add_edge(i, N + a, 1);
    }
  }
  
  max_flow();

  add_edge(S, N + M, 1);
  rep (i, M) add_edge(N + M, N + i, 1);

  if (max_flow() > 0) {
    puts("Alice");
  }
  else {
    puts("Bob");
  }

  // printf("%d\n", max_flow());

  return 0;
}
