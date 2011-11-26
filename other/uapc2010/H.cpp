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

typedef long long ll;

const int INF = 87654321;

double fwd[110];
double bwd[110];

int main() {
  for (;;) {
    int N, M, P;
    int adj[110][110];
    scanf("%d%d%d", &N, &M, &P);
    if (!N) return 0;
    
    rep (i, N) rep (j, N) adj[i][j] = INF;
    rep (i, M) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      adj[a][b] = c;
      adj[b][a] = c;
    }

    int dst[110][110];
    memcpy(dst, adj, sizeof(dst));
    rep (k, N) rep (i, N) rep (j, N) dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
    rep (i, N) dst[i][i] = 0;

    vector<pair<int, int> > vs(N);
    
    // fwd
    rep (i, N) vs[i] = mp(dst[0][i], i);
    sort(all(vs));
    memset(fwd, 0, sizeof(fwd));
    fwd[0] = 1.0;
    rep (i, vs.size()) {
      int v = vs[i].second;
      // printf(" fwd[%d]: %.f\n", v, fwd[v]);
      rep (w, N) {
        if (dst[0][v] + adj[v][w] + (ll)dst[w][N - 1] == dst[0][N - 1]) {
          fwd[w] += fwd[v];
        }
      }
    }

    // bwd
    rep (i, N) vs[i] = mp(dst[i][N - 1], i);
    sort(all(vs));
    memset(bwd, 0, sizeof(bwd));
    bwd[N - 1] = 1.0;
    rep (i, vs.size()){
      int v = vs[i].second;
      // printf(" bwd[%d]: %.f\n", v, bwd[v]);
      rep (w, N) {
        if (dst[0][w] + adj[w][v] + (ll)dst[v][N - 1] == dst[0][N - 1]) {
          bwd[w] += bwd[v];
        }
      }
    }

    double tot = fwd[N - 1];
    rep (i, P) {
      int v;
      scanf("%d", &v);
      printf("%.10f\n", bwd[v] * fwd[v] / tot);
    }
    puts("");
  }
}

