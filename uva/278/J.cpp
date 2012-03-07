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
#include <cstdarg>
#include <sys/time.h>
#include <climits>
#include <bitset>
using namespace std;


#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair


#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>

struct __bench__ {
  double start;
  char msg[100];
  __bench__(const char* format, ...)
  __attribute__((format(printf, 2, 3)))
  {
    va_list args;
    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    start = sec();
  }
  ~__bench__() {
    fprintf(stderr, "%s: %.6f sec\n", msg, sec() - start);
  }
  double sec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
  }
  operator bool() { return false; }
};

#define benchmark(...) if(__bench__ __b__ = __bench__(__VA_ARGS__));else




#include <stdint.h>

uint32_t xor128_x = 123456789;
uint32_t xor128_y = 362436069;
uint32_t xor128_z = 521288629;
uint32_t xor128_w = 88675123;

int xor128() {
  uint32_t t = xor128_x ^ (xor128_x << 11);
  xor128_x = xor128_y; xor128_y = xor128_z; xor128_z = xor128_w;
  return abs(int(xor128_w = (xor128_w ^ (xor128_w >> 19)) ^ (t ^ (t >> 8))));
}

void xor128_sxor128(uint32_t w) {
  xor128_w = w;
  rep (i, 10) xor128();
}




typedef unsigned long long ull;

const int MAX_NODE = 1000000;

struct node_t {
  char val;
  ull hsh;

  int des;  // # of its descendants
  node_t *lch, *rch;
};

node_t nodes[MAX_NODE];
int nodes_p = 0;

ull hsh_pow[1000010];
inline int des(node_t *t) { return t ? t->des : 0; }
inline ull hsh(node_t *t) { return t ? t->hsh : 0; }

pair<ull, int> merge_hsh(pair<ull, int> l, pair<ull, int> r) {
  return mp(l.first * hsh_pow[r.second] + r.first,
            l.second + r.second);
}

node_t *update(node_t *t) {
  assert(t);
  t->des = des(t->lch) + 1 + des(t->rch);
  t->hsh = merge_hsh(mp(hsh(t->lch), des(t->lch)),
           merge_hsh(mp(t->val, 1),
                     mp(hsh(t->rch), des(t->rch)))).first;
  return t;
}

node_t *new_node(char val) {
  node_t *t = &nodes[nodes_p++];
  t->val = val - '0';
  t->lch = t->rch = NULL;
  update(t);
  return t;
}

pair<ull, int> hsh_btw(node_t *t, int b, int e) {  // max of [b, e)
  if (!t || e <= 0 || des(t) <= b) return mp(0, 0);
  if (b <= 0 && des(t) <= e) return mp(hsh(t), des(t));

  int lde = des(t->lch);
  pair<ull, int> s = hsh_btw(t->lch, b, e);
  if (b <= lde && lde < e) s = merge_hsh(s, mp(t->val, 1));
  s = merge_hsh(s, hsh_btw(t->rch, b - lde - 1, e - lde - 1));
  return s;
}


node_t *merge(node_t *l, node_t *r) {
  if (!l || !r) return !l ? r : l;

  if (xor128() % (des(l) + des(r)) < des(l)) {
    l->rch = merge(l->rch, r);
    return update(l);
  } else {
    r->lch = merge(l, r->lch);
    return update(r);
  }
}

pair<node_t*, node_t*> split(node_t *t, int k) {  // [0, k), [k, n)
  assert(0 <= k && k <= des(t));
  if (!t) return mp((node_t*)NULL, (node_t*)NULL);

  if (k <= des(t->lch)) {
    pair<node_t*, node_t*> s = split(t->lch, k);
    t->lch = s.second;
    return mp(s.first, update(t));
  } else {
    pair<node_t*, node_t*> s = split(t->rch, k - des(t->lch) - 1);
    t->rch = s.first;
    return mp(update(t), s.second);
  }
}

node_t *insert(node_t *x, node_t *t, int k) {
  pair<node_t*, node_t*> s = split(t, k);
  return merge(merge(s.first, x), s.second);

  if (xor128() % (des(t) + 1) == 0) {
    pair<node_t*, node_t*> s = split(t, k);
    x->lch = s.first;
    x->rch = s.second;
    return update(x);
  } else {
    if (k <= des(t->lch)) t->lch = insert(x, t->lch, k);
    else t->rch = insert(x, t->rch, k - des(t->lch) - 1);
    return update(t);
  }
}

node_t *erase(node_t *t, int k) {
  pair<node_t*, node_t*> s1 = split(t, k);
  pair<node_t*, node_t*> s2 = split(s1.second, 1);
  return merge(s1.first, s2.second);  // Happy memory leak!

  if (k == des(t->lch)) {
    // Happy memory leak!
    return merge(t->lch, t->rch);
  } else if (k < des(t->lch)) {
    t->lch = erase(t->lch, k);
    return update(t);
  } else {
    t->rch = erase(t->rch, k - des(t->lch) - 1);
    return update(t);
  }
}

node_t *get(node_t *t, int k) {
  if (k < des(t->lch)) return get(t->lch, k);
  else if (k == des(t->lch)) return t;
  else return get(t->rch, k - des(t->lch) - 1);
}



void show(node_t *t, int d = 0) {
  if (!t) return;
  show(t->lch, d + 1);
  printf("%*s[%p: %c %llu]", d, "", t, t->val + '0', t->hsh);
  cout << bitset<20>(t->hsh) << endl;
  show(t->rch, d + 1);
}

node_t *construct(int n, char *vals) {
  if (n == 0) return NULL;
  int k = n / 2;
  node_t *t = new_node(vals[k]);
  t->lch = construct(k, vals);
  t->rch = construct(n - k - 1, vals + k + 1);
  return update(t);
}




char a[1000010];

int main(int argc, char **argv) {
  hsh_pow[0] = 1;

  for (int N, M; 2 == scanf("%d%d", &N, &M); ) {
    scanf("%s", a);

    rep (i, N + M) hsh_pow[i + 1] = hsh_pow[i] * 3;  // TODOOOOOOOOOOOOOOOOOOOOOO
    nodes_p = 0;

    node_t *r_fwd = NULL, *r_bwd = NULL;

    benchmark("construct") {
      r_fwd = construct(N, a);
      reverse(a, a + N);
      r_bwd = construct(N, a);
    }

    int cnt4 = 0;

    benchmark("query")
    rep (i, M) {
      int cmd;
      scanf("%d", &cmd);

      switch (cmd) {
        case 1: {
          int p;
          char c;
          scanf("%d %c", &p, &c);
          r_fwd = insert(new_node(c), r_fwd, p);
          r_bwd = insert(new_node(c), r_bwd, N - p);
          ++N;
          break;
        }
        case 2: {
          int p;
          scanf("%d", &p);
          --p;
          r_fwd = erase(r_fwd, p);
          r_bwd = erase(r_bwd, N - p - 1);
          --N;
          break;
        }
        case 3: {
          int p1, p2;
          scanf("%d%d", &p1, &p2);
          --p1;

          pair<node_t*, node_t*>
              s_fwd1 = split(r_fwd, p1),
              s_fwd2 = split(s_fwd1.second, p2 - p1),
              s_bwd1 = split(r_bwd, N - p2),
              s_bwd2 = split(s_bwd1.second, p2 - p1);

          r_fwd = merge(s_fwd1.first, merge(s_bwd2.first, s_fwd2.second));
          r_bwd = merge(s_bwd1.first, merge(s_fwd2.first, s_bwd2.second));
          break;
        }
        case 4: {
          ++cnt4;

          int p1, p2;
          scanf("%d%d", &p1, &p2);
          --p1; --p2;
          int lb = 0, ub = N - p2 + 1;
          while (ub - lb > 1) {
            int x = (lb + ub) / 2;
            if (hsh_btw(r_fwd, p1, p1 + x).first == hsh_btw(r_fwd, p2, p2 + x).first) {
              lb = x;
            } else {
              ub = x;
            }
          }
          printf("%d\n", lb);
          break;
        }
      }
    }
  }

  return 0;
}
