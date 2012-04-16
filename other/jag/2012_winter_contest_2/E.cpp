#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair

const ll MOD = 1000000007;

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

ll pow_mod(ll a, ll k) {
  if (k == 0) return 1;
  ll t = pow_mod(a, k / 2);
  return t * t % MOD * (k % 2 ? a : 1) % MOD;
}

ll inverse(ll a) {
  return pow_mod(a, MOD - 2);
}

int H, W;
char fld[510][20];

bool vis[510][20];
int parx[510][20];
int pary[510][20];

int dfs(int x, int y, int px, int py) {
  if (x < 1 || W < x || y < 1 || H < y) return 0;
  if (vis[y][x]) return 0;
  
  vis[y][x] = true;
  parx[y][x] = px;
  pary[y][x] = py;
  
  int res = fld[y][x] == '.' ? 1 : 0;
  rep (d, 4) {
    int tx = x + dx[d];
    int ty = y + dy[d];
    res += dfs(tx, ty, x, y);
  }
  return res;
}


ll mat[10010][100];

#define MAT(i, j) mat[(i)][(j) - (i) + 2 * W]

int vid(int y, int x) {
  return (y - 1) * W + (x - 1);
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d", &H, &W);
    if (H == 0 && W == 0) return 0;
    printf("Case %d: ", ca);
    
    memset(fld, '#', sizeof(fld));
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        scanf(" %c", &fld[y][x]);
      }
    }
    
    memset(vis, 0, sizeof(vis));
    int cc_size = -1, free_cell = 0;
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        if (fld[y][x] == '.') {
          if (cc_size == -1) cc_size = dfs(x, y, -1, -1);
          ++free_cell;
        }
      }
    }
    if (cc_size != free_cell) {
      // printf("%d %d\n", cc_size, free_cell);
      
      // DISCONNECTED!
      puts("0");
      continue;
    }
    
    // TODO: check connectivity
    int N = W * H;
    memset(mat, 0, sizeof(mat));

    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        int i = vid(y, x);

        if (fld[y][x] == '#') {
          // printf("%d %d -- %d %d\n", x, y, parx[y][x], pary[y][x]);
          
          int ti = vid(pary[y][x], parx[y][x]);
          MAT(i, ti) = -1;
          MAT(ti, i) = -1;
          
          MAT( i,  i) += 1;
          MAT(ti, ti) += 1;
        } else {
          int deg = 0;
          rep (d, 4) {
            int tx = x + dx[d];
            int ty = y + dy[d];
            if (fld[ty][tx] == '#') continue;
            MAT(i, vid(ty, tx)) = -1;
            MAT(i, i) += 1;
          }
        }
      }
    }

    // rep (i, N) {
    //   rep (j, N) printf("%3lld ", MAT(i, j));
    //   puts("");
    // }

    --N;
    ll ans = 1;
    rep (i, N) {
      // rep (y, N) { rep (x, N) printf("%3lld ", MAT(y, x)); puts(""); } puts("");

      for (int k = 0; k <= W; ++k) {
        int ti = i + k;
        if (MAT(ti, i) != 0) {
          // swap row i & row (i + k)
          for (int j = i; j <= i + 2 * W; ++j) swap(MAT(i, j), MAT(ti, j));
          break;
        }
      }
      
      if (MAT(i, i) == 0) {
        ans = 0;
        break;
      }

      ll x = MAT(i, i);
      (ans *= x) %= MOD;
      ll invx=inverse(x);
      for (int j = i; j <= i + 2 * W; ++j) (MAT(i, j) *= invx) %= MOD;

      for (int k = 1; k <= W; ++k) {
        int ti = i + k;
        // eliminate row (i + k)
        x = MAT(ti, i);
        for (int j = i; j <= i + 2 * W; ++j) (MAT(ti, j) -= x * MAT(i, j)) %= MOD;
      }
    }
    (ans += MOD) %= MOD;
    printf("%lld\n", ans);
  }
}
