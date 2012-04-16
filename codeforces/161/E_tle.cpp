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

const int MAX_N = 1000010;

int prime[MAX_N], prime_n;
bool is_composite[MAX_N + 1];

void sieve(int n) {
  is_composite[0] = is_composite[1] = true;
  for (int i = 2; i * i <= n; i++) {
    if (is_composite[i]) continue;
    for (int j = i; i * j <= n; j++) is_composite[i * j] = true;
  }
  prime_n = 0;
  for (int i = 2; i <= n; i++) {
    if (!is_composite[i]) prime[prime_n++] = i;
  }
}

ll pow10_tbl[20];

void init() {
  pow10_tbl[0] = 1;
  for (int i = 1; i < 20; i++) pow10_tbl[i] = pow10_tbl[i - 1] * 10;
}

ll pow10(int p) {
  return pow10_tbl[p];
}

int len(ll x) {
  int l = 1;
  for (x /= 10; x > 0; x /= 10) l++;
  return l;
}

ll rev(ll x) {
  ll r = 0;
  for (; x > 0; x /= 10) r = r * 10 + x % 10;
  return r;
}

ll concat(ll a, ll b) {
  return a * pow10(len(b)) + b;
}

int get(ll a, int i) {
  return a / pow10(i) % 10;
}

ll edit(ll a, int i, int d) {
  ll b = pow10(i);
  return (a / b / 10) * b * 10 + d * b + a % b;
}

int lexcmp(ll a, ll b) {
  int al = len(a), bl = len(b);
  if (al < bl) a *= pow10(bl - al);
  if (bl < al) b *= pow10(al - bl);
  if (a != b) return a < b ? -1 : 1;
  return al < bl ? -1 : al == bl ? 0 : 1;
}

int N;
vector<int> ps[10][100000];

int mat[20][20];
void show() {
  rep (i, N) {
    rep (j, N) printf("%2d ", mat[i][j]);
    puts("");
  }
}

int ans;
int J[20], H[20];

void search(int r, int c) {
  assert(mat[r][c] == -1);

  if (r == N) {
    // show();
    ++ans;
    return;
  }
  if (c == N) {
    search(r + 1, r + 1);
    return;
  }

  // puts("--");
  // show();
  // puts("--");

  for (int d = 0; d <= 9; ++d) {
    mat[r][c] = mat[c][r] = d;

    { ++J[r];  H[r] = H[r] * 10 + d; }
    if (c != r) { ++J[c]; H[c] = H[c] * 10 + d; }

    if (ps[J[r]][H[r]].empty()) goto ng;
    if (ps[J[c]][H[c]].empty()) goto ng;

    // rep (i, N) {
    //   int j = 0, h = 0;
    //   for (; j < N; ++j) {
    //     if (mat[i][j] == -1) break;
    //     h = h * 10 + mat[i][j];
    //   }

    //   assert(J[i] == j && H[i] == h);

    //   if (ps[j][h].empty()) goto ng;
    // }

    search(r, c + 1);

 ng:;
    mat[r][c] = mat[c][r] = -1;

    { --J[r]; H[r] /= 10; }
    if (c != r) { --J[c]; H[c] /= 10; }
  }
}

int main() {
  sieve(99999);
  init();

  int T;
  scanf("%d", &T);
  rep (t, T) {
    int P;
    scanf("%d", &P);

    N = len(P);

    rep (i, N + 1) rep (j, pow10(i)) ps[i][j].clear();
    rep (k, prime_n) {
      rep (i, N + 1) {
        int p = prime[k];
        if (p >= pow10(N)) break;
        int j = prime[k] / pow10(N - i) % pow10(i);
        ps[i][j].pb(prime[k]);
      }
    }

    /*
    rep (i, N + 1) {
      rep (j, pow10(i)) {
        if (ps[i][j].empty()) continue;
        printf("%d %0*d: ", i, i, j);
        rep (k, ps[i][j].size()) printf("%0*d ", N, ps[i][j][k]);
        puts("");
      }
    }
    break;
    */

    memset(mat, -1, sizeof(mat));
    rep (i, N) mat[i][0] = mat[0][i] = get(P, N - i - 1);
    // show();

    rep (i, N) {
      J[i] = 1;
      H[i] = get(P, N - i - 1);
    }

    ans = 0;
    search(1, 1);
    printf("%d\n", ans);
  }

  return 0;
}

