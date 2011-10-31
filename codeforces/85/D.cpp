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

typedef int key_t;

struct node_t {
  key_t key;
  node_t *ch[2]; // ch = {&left, &right};
  double pri;

  int cnt;
  ll sum[5];
  bool memed;

  node_t(const key_t &k, double p)
      : key(k), pri(p), memed(false) {
    ch[0] = ch[1] = 0;

    cnt = 1;
    rep (i, 5) sum[i] = 0;
  }
};


node_t *rotate(node_t *t, int b) {
  node_t *s = t->ch[1-b]; t->ch[1-b] = s->ch[b]; s->ch[b] = t;
  s->memed = t->memed = false;
  return s;
}

node_t *insert(node_t *t, const key_t &k, double p) {
  if (!t) return new node_t(k, p);
  else if (k == t->key) { // キーの重複 => 更新
    t->memed = false;
    return t;
  }
  int b = !(k < t->key);
  t->ch[b] = insert(t->ch[b], k, p);
  if (t->pri > t->ch[b]->pri) t = rotate(t, 1-b);
  t->memed = false;
  return t;
}

node_t *insert(node_t *t, const key_t &k) {
  return insert(t, k, rand() / (double)RAND_MAX);
}

node_t *erase(node_t *t, const key_t &key) {
  if (!t) {
    return NULL;
  }
  if (key == t->key) {
    if (!t->ch[0] && !t->ch[1]) return NULL; // memory leak
    t = rotate(t, t->ch[0] ? t->ch[1] ? (t->ch[0]->pri < t->ch[1]->pri) : 1 : 0);
    t = erase(t, key);
  } else {
    int b = !(key < t->key);
    t->ch[b] = erase(t->ch[b], key);
  }
  t->memed = false;
  return t;
}

inline int count(node_t *t) {
  if (!t) return 0;
  else return t->cnt;
}

void eval(node_t *t) {
  if (!t) return;
  if (!t->memed) {

    node_t *lch = t->ch[0], *rch = t->ch[1];
    eval(lch);
    eval(rch);

    int lcnt = count(lch);
    int rcnt = count(rch);
    t->cnt = lcnt + 1 + rcnt;

    rep (i, 5) t->sum[i] = 0;
    if (lch) rep (i, 5) t->sum[i] = lch->sum[i];
    t->sum[lcnt % 5] += t->key;
    if (rch) rep (i, 5) t->sum[(lcnt + 1 + i) % 5] += rch->sum[i];

    // printf("node %d (%d, %d)", t->key, lch ? lch->key : -1, rch ? rch->key : -1);
    // rep (i, 5) printf(" %lld", t->sum[i]); puts("");

    t->memed = true;
  }
}


pair<node_t*, node_t*> split(node_t *t, key_t k) { // (-inf, k), (k, inf)
  node_t *dmy = insert(t, k, -1.0); // welcome to a memory leak !
  return make_pair(dmy->ch[0], dmy->ch[1]);
}

node_t *merge(node_t *l, node_t *r, key_t k) {
  node_t *dmy = new node_t(k, -1.0);
  dmy->ch[0] = l; dmy->ch[1] = r;
  return erase(dmy, k);
}

void print(node_t *t, int d = 0) {
  if (!t) return;
  print(t->ch[0], d + 1);
  printf("%*s%d\n", d, "", t->key);
  print(t->ch[1], d + 1);
}

void test() {
  vector<int> vs;
  node_t *root = NULL;
  for (;;) {
    if (rand() % 3 == 0) {
      int x = rand();
      if (binary_search(all(vs), x)) continue;

      vs.push_back(x);
      sort(all(vs));
      root = insert(root, x);
      puts("INSERT");
    }
    else if (rand() % 2 == 0) {
      if (vs.empty()) continue;

      int x = vs[rand() % vs.size()];
      vs.erase(remove(all(vs), x), vs.end());
      root = erase(root, x);
      puts("ERASE");
    }
    else {
      eval(root);
      ll res = root ? root->sum[2] : 0;

      ll ans = 0;
      rep (i, vs.size()) if (i % 5 == 2) ans += vs[i];
      assert(ans == res);
      printf("OK: %lld\n", ans);
    }
  }
}

int main() {
  // test();

  int Q;
  scanf("%d", &Q);
  node_t *root = NULL;

  rep (q, Q) {
    char buf[256];
    int x;
    scanf("%s", buf);
    if (buf[0] == 'a') {
      scanf("%d", &x);
      root = insert(root, x);
    }
    else if (buf[0] == 'd') {
      scanf("%d", &x);
      // print(root);
      root = erase(root, x);
      // puts("=======");
      // print(root);
    }
    else {
      eval(root);
      if (!root) puts("0");
      else cout << root->sum[2] << endl;
    }
  }

  return 0;
}

