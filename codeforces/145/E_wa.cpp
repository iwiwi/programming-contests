// 本来は部分列のうちで最長のものを答える問題
// このコードは部分文字列のうちで最長のものを答える

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

struct seg_t {
  bool ld, rd;
  int ll0, ll01;
  int rl0, rl01;
  int in[2];
  int L;
};

int n;
bool inv[4 * MAX_N];
seg_t seg[4 * MAX_N];  // |inv| is already applied

inline void upmax(int &x, int y) { x = max(x, y); }

void update(int k, bool flip = false) {
  seg_t &S = seg[k];
  const seg_t &l = seg[k * 2 + 1], &r = seg[k * 2 + 2];

  if (k < 0 + n - 1) {
    S.ld = l.ld;
    S.rd = r.rd;

    S.ll0 = l.ll0;
    if (l.ll0 == l.L && l.ld == r.ld) S.ll0 += r.ll0;

    S.rl0 = r.rl0;
    if (r.rl0 == r.L && r.rd == l.rd) S.rl0 += l.rl0;

    S.ll01 = l.ll01;
    if (l.ll0 == l.L) S.ll01 += l.ld == r.ld ? r.ll01 : r.ll0;
    else if (l.ll01 == l.L && l.ld != r.ld) S.ll01 += r.ll0;

    S.rl01 = r.rl01;
    if (r.rl0 == r.L) S.rl01 += r.rd == l.rd ? l.rl01 : l.rl0;
    else if (r.rl01 == r.L && r.rd != l.rd) S.rl01 += l.rl0;

    rep (i, 2) S.in[i] = max(l.in[i], r.in[i]);

    if (l.rd == r.ld) {
      rep (i, 2) upmax(S.in[i], l.rl0 + r.ll0);
      upmax(S.in[ l.rd], l.rl0  + r.ll01);
      upmax(S.in[!l.rd], l.rl01 + r.ll0 );
    } else {
      upmax(S.in[l.rd], l.rl0 + r.ll0);
    }

    if (flip) inv[k] = !inv[k];
  } else if (flip) {
    S.ld = !S.ld;
    S.rd = !S.rd;
  }

  if (inv[k]) {
    S.ld = !S.ld;
    S.rd = !S.rd;
    swap(S.in[0], S.in[1]);
  }
}

void init(int n_, bool *a) {
  for (n = 1; n < n_; n *= 2);
  memset(inv, 0, sizeof(inv));

  rep (i, n_) {
    int k = i + n - 1;
    seg_t &s = seg[k];
    s.ld = s.rd = a[i];
    s.ll0 = s.ll01 = s.rl0 = s.rl01 = s.in[0] = s.in[1] = 1;
    s.L = 1;
  }
  for (int i = n_; i < n; ++i) {
    int k = i + n - 1;
    seg_t &s = seg[k];
    s.ld = s.rd = 0;
    s.ll0 = s.ll01 = s.rl0 = s.rl01 = s.in[0] = s.in[1] = s.L = 0;
  }

  for (int k = (0 + n - 1) - 1; k >= 0; --k) {
    seg[k].L = seg[k * 2 + 1].L + seg[k * 2 + 2].L;
    update(k);
  }
}

void query(int a, int b, int k = 0, int l = 0, int r = 0) { // [a, b)
  if (k == 0) r = n;
  if (r <= a || b <= l) return;
  if (a <= l && r <= b) {
    update(k, true);
  }
  else {
    query(a, b, k * 2 + 1, l, (l + r) / 2);
    query(a, b, k * 2 + 2, (l + r) / 2, r);
    update(k, false);
  }
}

int count() {
  return seg[0].in[0];
}


namespace naive {
int N;
char S[1000010];
int count() {
  int r = 0;
  int l = '7', c = 0;
  rep (i, N) {
    if (S[i] != l && S[i] == '4') c = 0;
    r = max(r, ++c);
    l = S[i];
  }
  return r;
}

void update(int b, int e) {
  for (int i = b; i < e; ++i) S[i] = S[i] == '4' ? '7' : '4';
}
}  // naive


char buf[1000010];
bool A[1000010];

int main() {
  {
    srand(0);
    int N = 10000, Q = 1000000;
    rep (i, N) buf[i] = rand() % 2 ? '4' : '7';

    rep (i, N) A[i] = buf[i] == '7';
    init(N, A);

    naive::N = N; rep (i, N) naive::S[i] = buf[i];
    rep (i, N) printf("%c", naive::S[i]); puts("");

    rep (i, Q) {
      int b = rand() % N;
      int e = rand() % N;
      if (b > e) swap(b, e);
      query(b, e + 1);
      naive::update(b, e + 1);
      // printf("[%d, %d]\n", b + 1, e + 1); rep (i, N) printf("%c", naive::S[i]); puts("");

      if (count() != naive::count()) {
        puts("Wrong Answer");
        printf("%d -> %d\n", naive::count(), count());
        break;
      }
    }
    return 0;
  }

  int N_, Q;
  while (2 == scanf("%d%d", &N_, &Q)) {
    scanf("%s", buf);
    rep (i, N_) A[i] = buf[i] == '7';
    init(N_, A);

    rep (q, Q) {
      scanf("%s", buf);
      if (buf[0] == 'c') {
        printf("%d\n", count());
      } else {
        int b, e;
        scanf("%d%d", &b, &e);
        --b;
        // printf("[%d, %d)\n", b, e);
        query(b, e);
      }
    }
  }

  return 0;
}

