#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define pb push_back

typedef pair<int, int> pii;

int B, M;
vector<pii> adj[110][2];
int col[110];

void search(int b, int c) {
  if (col[b] != -1) {
    if (col[b] != c) throw 0;  // oh!!!!
    return;
  }
  col[b] = c;
  rep (i, adj[b][c].size()) search(adj[b][c][i].first, adj[b][c][i].second);
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d", &B, &M);
    if (B == 0 && M == 0) return 0;

    rep (b, B) rep (i, 2) adj[b][i].clear();
    rep (i, M) {
      int k;
      scanf("%d", &k);
      vector<pii> v(k);
      rep (j, k) {
        char c;
        scanf("%d %c", &v[j].first, &c);
        --v[j].first;
        v[j].second = (c == 'y' ? 1 : 0);
      }
      if (k <= 2) {
        rep (a, k) adj[v[a].first][1 - v[a].second].pb(v[a]);
      } else {
        rep (a, k) rep (b, k) if (a != b) adj[v[a].first][1 - v[a].second].pb(v[b]);
      }
    }

    printf("Case %d: ", ca);
    char ans[110];
    rep (b, B) {
      int msk = 0;
      rep (c, 2) {
        memset(col, -1, sizeof(col));
        try {
          search(b, c);
          msk |= 1 << c;
        } catch (...) {}
      }
      if (msk == 0) goto imp;
      // printf("%d: %d\n", b, msk);
      ans[b] = "Xny?"[msk];
    }
    ans[B] = '\0';
    // rep (i, B) printf("%d \n", ans[i]);
    puts(ans);
    continue;
  imp:
    puts("impossible");
  }
}
