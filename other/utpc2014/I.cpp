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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

const int MAX_NODE = 1000000;
typedef pair<int, int> pii;

struct node_t {
  // <WEIGHT, ID>
  pii val;  // !!!
  pii min;

  int des;
  node_t *lch, *rch, *par;
};

node_t nodes[MAX_NODE];
int nodes_p = 0;

inline int des(node_t *t) { return t ? t->des : 0; }
inline pii min(node_t *t) { return t ? t->min : make_pair(INT_MAX, INT_MAX); }  // !!!

node_t *update(node_t *t) {
  t->des = des(t->lch) + 1 + des(t->rch);
  t->min = min(min(min(t->lch), t->val), min(t->rch));  // !!!
  return t;
}

node_t *new_node(pii val) {
  node_t *t = &nodes[nodes_p++];
  t->lch = t->rch = NULL;
  t->val = val;  // !!!
  update(t);
  return t;
}

inline void link_lch(node_t *par, node_t *lch) {
  par->lch = lch;
  if (lch) lch->par = par;
}

inline void link_rch(node_t *par, node_t *rch) {
  par->rch = rch;
  if (rch) rch->par = par;
}

node_t *merge(node_t *l, node_t *r) {
  if (!l || !r) return !l ? r : l;

  if (rand() % (des(l) + des(r)) < des(l)) {
    link_rch(l, merge(l->rch, r));
    return update(l);
  } else {
    link_lch(r, merge(l, r->lch));
    return update(r);
  }
}

pair<node_t*, node_t*> split(node_t *t, int k) {  // [0, k), (k, n)
  if (!t) return mp((node_t*)NULL, (node_t*)NULL);

  if (k == des(t->lch)) {
    if (t->lch) t->lch->par = NULL;
    if (t->rch) t->rch->par = NULL;
    return mp(t->lch, t->rch);
  } else if (k < des(t->lch)) {
    pair<node_t*, node_t*> s = split(t->lch, k);
    link_lch(t, s.second);
    t->par = NULL;
    return mp(s.first, update(t));
  } else {
    pair<node_t*, node_t*> s = split(t->rch, k - des(t->lch) - 1);
    link_rch(t, s.first);
    t->par = NULL;
    return mp(update(t), s.second);
  }
}

int N;
vector<pair<int, int> > adj[100010];

struct edge_t {
  int id;
  int a, b, c;
  node_t *t[2];
  bool r;
} es[100010];


void print(node_t *p, int d = 0) {
  if (p == NULL) return;
  print(p->lch, d + 1);
  edge_t &e = es[p->val.second];
  printf("%*s[%d,%d] <%d, %d, %d>\n", d, "", p->min.first, p->min.second, e.a+1, e.b+1, e.c);
  print(p->rch, d + 1);
}


// Euler-Tour ------------------------------
node_t *root;

void search(int v, int p) {
  for (auto a : adj[v]) {
    int w = a.first;
    if (w == p) continue;
    edge_t &e = es[a.second];

    {
      node_t *n = new_node(make_pair(e.c, e.id));
      e.t[0] = n;
      root = merge(root, n);
    }

    search(w, v);

    {
      node_t *n = new_node(make_pair(e.c, e.id));
      e.t[1] = n;
      root = merge(root, n);
    }
  }
}

pair<node_t*, node_t*> split_by_node(node_t *n) {
  int k = des(n->lch);

  for (; n->par != NULL; n = n->par) {
    node_t *par = n->par;
    if (par->rch == n) k += des(par->lch) + 1;
  }

  return split(n, k);
}

int main() {
  while (1 == scanf("%d", &N)) {
    rep (v, N) adj[v].clear();

    rep (i, N - 1) {
      edge_t &e = es[i];
      e.id = i;
      scanf("%d%d%d", &e.a, &e.b, &e.c);
      --e.a;
      --e.b;

      adj[e.a].emplace_back(e.b, e.id);
      adj[e.b].emplace_back(e.a, e.id);
      e.r = false;
    }

    root = NULL;
    nodes_p = 0;
    search(0, -1);

    // print(root); puts("--");

    int Q;
    scanf("%d", &Q);
    rep (q, Q) {
      int t, eid;
      scanf("%d%d", &t, &eid);
      --eid;
      edge_t &e = es[eid];

      if (t == 1) {
        int d;
        scanf("%d", &d);

        e.c += d;
        rep (i, 2) {
          node_t *n = e.t[i];
          n->val.first += d;

          while (n != NULL) {
            update(n);
            n = n->par;
          }
        }
      } else {
        if (e.r) {
          puts("-1");
          continue;
        }

        // Find the connected component
        node_t *n = e.t[0];
        while (n->par != NULL) n = n->par;
        int cut_eid = n->min.second;
        edge_t &cut_e = es[cut_eid];
        printf("%d\n", cut_eid + 1);
        cut_e.r = true;

        // puts("\n\n\n"); print(n);

        node_t *l, *m, *r;
        tie(l, m) = split_by_node(cut_e.t[0]);
        tie(m, r) = split_by_node(cut_e.t[1]);

        // print(l); puts("=="); print(m); puts("=="); print(r);

        node_t *lr = merge(l, r);
        // puts("VV"); print(lr);
      }

      // print(root);
      // puts("--");
    }
  }

  return 0;
}
