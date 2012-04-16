#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair

int N, T, K;

int par[100010];
bool base[100010];

int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}


int M;
pair<int, pair<int, int> > E[100010];

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d%d", &N, &T, &K);
    if (N == 0) return 0;

    M = N - 1;
    rep (i, M) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      --a;
      --b;
      E[i] = mp(c, mp(a, b));
    }

    memset(base, 0, sizeof(base));
    rep (i, T) {
      int v;
      scanf("%d", &v);
      --v;
      base[v] = true;
    }
    rep (v, N) par[v] = v;

    sort(E, E + M);
    reverse(E, E + M);
    int q = T - K - 1, cst = 0;
    rep (i, M) {
      int c = E[i].first;
      int v = root(E[i].second.first);
      int w = root(E[i].second.second);

      if (base[v] && base[w] && q == 0) {
        cst += c;
      } else {
        // printf("merge: %d-%d\n", v, w);
        if (base[v] && base[w]) --q;
        
        par[v] = w;
        base[w] |= base[v];
      }
    }

    printf("Case %d: %d\n", ca, cst);
  }
}
