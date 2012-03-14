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

const int MAX_N = 50010;

typedef int edge_t;  // !!!

edge_t dummy_e = 1 << 30;

struct node_t {
  // MODIFY HERE!!!
  int col, pai;
  static int get_col(node_t *t) { return !t ? 0 : t->pai ? t->pai : t->col; }

  node_t *pp, *lp, *rp;
  edge_t pe, le, re;
  int cnt;
  bool rev;

  node_t() {
    pp = lp = rp = NULL;
    pe = le = re = dummy_e;
    rev = false;
    pai = 0;
    update();
  }

  bool is_root() {
    return !pp || (pp->lp != this && pp->rp != this);
  }

  void update() {
    if (rev) {
      if (lp) lp->rev ^= true;
      if (rp) rp->rev ^= true;
      swap(lp, rp);
      swap(le, re);
      rev = false;
    }
    cnt = 1 + (lp ? lp->cnt : 0) + (rp ? rp->cnt : 0);

    // MODIFY HERE!!!
    if (pai) {
      if (lp) { le = lp->pe = pai; lp->pai = pai; }
      if (rp) { re = rp->pe = pai; rp->pai = pai; }
      pai = 0;
    }
    col = le | re | get_col(lp) | get_col(rp);
  }

  void rotr() {
    node_t *q = pp, *r = q->pp;
    if ((q->lp = rp)) {
      rp->pp = q;
      swap(pe, rp->pe);
    } else {
      swap(re, q->le);
    }
    rp = q; q->pp = this;
    if ((pp = r)) {
      if (r->lp == q) r->lp = this;
      if (r->rp == q) r->rp = this;
    }
    swap(pe, q->pe);
    q->update();
    update();
  }

  void rotl() {
    node_t *q = pp, *r = q->pp;
    if ((q->rp = lp)) {
      lp->pp = q;
      swap(pe, lp->pe);
    } else {
      swap(le, q->re);
    }
    lp = q; q->pp = this;
    if ((pp = r)) {
      if (r->lp == q) r->lp = this;
      if (r->rp == q) r->rp = this;
    }
    swap(pe, q->pe);
    q->update();
    update();
  }

  void splay() {
    while (!is_root()) {
      node_t *q = pp;
      if (q->is_root()) {
        q->update();
        update();
        if (q->lp == this) rotr();
        else rotl();
      } else {
        node_t *r = q->pp;
        r->update();
        q->update();
        update();
        if (r->lp == q) {
          if (q->lp == this) { q->rotr(); rotr(); }
          else { rotl(); rotr(); }
        } else {
          if (q->rp == this) { q->rotl(); rotl(); }
          else { rotr(); rotl(); }
        }
      }
    }
  }
};

node_t nodes[MAX_N];

node_t *expose(node_t *x) {
  node_t *rp = NULL;
  edge_t re = dummy_e;
  for (node_t *p = x; p; p = p->pp) {
    p->splay();
    p->update();
    p->rp = rp; rp = p;
    p->re = re; re = p->pe;
    p->update();
  }
  x->splay();
  return x;
}

void cut(node_t *c) {
  expose(c);
  node_t *p = c->lp;
  assert(p && "|c| should have a parent");
  c->lp = NULL; c->le = dummy_e;
  p->pp = NULL; p->pe = dummy_e;
  c->update();
}

void connect(node_t *c, node_t *p, edge_t e) {
  expose(c);
  expose(p);
  assert(c->pp == NULL && "|c| should be a root of a tree");
  c->pp = p; p->rp = c;
  c->pe = e; p->re = e;
  p->update();
}

void evert(node_t *p) {
  node_t *r = expose(p);
  r->rev = true;
}

node_t *root(node_t *p) {
  p = expose(p);
  while (p->lp) p = p->lp;
  p->splay();
  return p;
}



int par[MAX_N], col[MAX_N];

int main() {
  for (int N, M; 2 == scanf("%d%d", &N, &M); ) {
    rep (i, N) {
      scanf("%d", par + i);
      --par[i];
    }
    rep (i, N) {
      scanf("%d", col + i);
      --col[i];
    }

    rep (i, N) if (par[i] != -1) connect(&nodes[i], &nodes[par[i]], 1 << col[i]);

    rep (iter, M) {
      int cmd, x, y, c;
      scanf("%d%d%d", &cmd, &x, &y);
      --x;
      --y;
      if (cmd == 1) {
        scanf("%d", &c);
        --c;
        if (x == y) continue;

        expose(&nodes[1]);

        if (par[x] != -1) cut(&nodes[x]);
        if (root(&nodes[y]) == &nodes[x]) {
          connect(&nodes[x], &nodes[par[x]], 1 << col[x]);
        } else {
          connect(&nodes[x], &nodes[y], 1 << c);
          par[x] = y;
          col[x] = c;
        }
      } else if (cmd == 2) {
        scanf("%d", &c);
        --c;

        node_t *r = root(&nodes[y]);
        if (r != root(&nodes[x])) {
          continue;
        } else {
          evert(&nodes[y]);
          node_t *p = expose(&nodes[x]);
          p->col = p->pai = 1 << c;
          evert(r);
        }
      } else {
        node_t *r = root(&nodes[y]);
        if (r != root(&nodes[x])) {
          puts("0 0");
        } else {
          evert(&nodes[y]);
          node_t *q = expose(&nodes[x]);
          int n = q->cnt - 1;
          int c = __builtin_popcount(q->col & ((1 << 30) - 1));
          printf("%d %d\n", n, c);
          evert(r);
        }
      }
    }

    return 0;
  }
}
