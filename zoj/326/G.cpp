#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <set>
#include <iostream>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define mp make_pair

const int INF = 987654321;

int N, K;
int W[1010];

vector<int> adj[1010];
int chn[1010];

int ans;

// maximize
vector<int> search(int v, int p) {
  chn[v] = 1;

  vector<int> res(K + 1, -INF);
  res[0] = W[v];

  rep (z, adj[v].size()) {
    if (adj[v][z] == p) continue;

    vector<int> chi = search(adj[v][z], v);
    chn[v] += chn[adj[v][z]];

    vector<int> nxt(K + 1, -INF);

    for (int i = 0; i <= K; ++i) {
      for (int j = 0; j <= K; ++j) {
        // connect ?
        if (i + j <= K && res[i] != -INF && chi[j] != -INF) {
          nxt[i + j] = max(nxt[i + j], res[i] + chi[j]);
        }

        // cut ?
        if (i + j + 1 <= K && res[i] != -INF && chi[j] != -INF) {
          nxt[i + j + 1] = max(nxt[i + j + 1], res[i]);
        }
      }
    }

    res = nxt;
  }

  // printf("%d: %d\n", v + 1, res[K]);

  if (p == -1) ans = max(ans, res[K]);
  else {
    int t = N - chn[v];
    for (int i = 1; i <= t; ++i) {
      if (K - i < 0) break;
      ans = max(ans, res[K - i]);
    }
  }

  return res;
}

int main() {
  while (2 == scanf("%d%d", &N, &K)) {
    rep (i, N) scanf("%d", &W[i]);

    rep (i, N) adj[i].clear();
    rep (i, N - 1) {
      int v, w;
      scanf("%d%d", &v, &w);
      --v;
      --w;
      adj[v].push_back(w);
      adj[w].push_back(v);
    }

    ans = -INF;
    search(0, -1);
    int ans_max = ans;

    rep (i, N) W[i] = -W[i];
    ans = -INF;
    search(0, -1);
    int ans_min = -ans;

    printf("%d %d\n", ans_min, ans_max);
  }
}
