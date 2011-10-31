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


typedef int val_t;
 
struct node_t {
  val_t val;
  node_t *ch[2]; // = {&left, &right};
  double pri;
 
  bool cached;
  int cnt;
  val_t max;
 
  node_t(const val_t &v, double p) 
    : val(v), pri(p), cached(false) { ch[0] = ch[1] = 0; }
};
 
 
void calc(node_t *t);
int count(node_t *t) { calc(t); return !t ? 0 : t->cnt; }
val_t max(node_t *t) { calc(t); return !t ? 0 : t->max; }
 
void calc(node_t *t) {
  if (!t || t->cached) return;
  t->cnt = count(t->ch[0]) + count(t->ch[1]) + 1;
  t->max = max(max(max(t->ch[0]), max(t->ch[1])), t->val);
  t->cached = true;
}
 
// val_t sum_by(node_t *t, int k) { // [0, k)
//   if (!t) return val_t();
//   int cl = count(t->ch[0]);
//   if (k <= cl) return sum_by(t->ch[0], k);
//   else return sum(t->ch[0]) + t->val + sum_by(t->ch[1], k-cl-1);
// }

node_t *rotate(node_t *t, int b) {
  node_t *s = t->ch[1-b]; t->ch[1-b] = s->ch[b]; s->ch[b] = t;
  s->cached = t->cached = false;
  return s;
}
 
node_t *get(node_t *t, int k) { // 0-indexed
  int cl = count(t->ch[0]);
  if (k < cl) return get(t->ch[0], k);
  else if (k == cl) return t;
  else return get(t->ch[1], k-cl-1);
}
 
node_t *insert(node_t *t, int k, const val_t &v, double p) {
  if (!t) return new node_t(v, p);
  int cl = count(t->ch[0]);

  int b = 0;
  if (k > cl) b = 1;
  else if (max(max(t->ch[1]), t->val) > v) b = 1;
  
  t->ch[b] = insert(t->ch[b], k - (b?(cl+1):0), v, p);
  if (t->pri > t->ch[b]->pri) t = rotate(t, 1-b);
  t->cached = false;
  return t;
}
 
node_t *insert(node_t *t, int k, const val_t &v) {
  return insert(t, k, v, rand() / (double)RAND_MAX);
}
 
node_t *erase(node_t *t, int k) {
  if (!t) return NULL;
  int cl = count(t->ch[0]);
  if (k == cl) {
    if (!t->ch[0] && !t->ch[1]) return NULL; // memory leak
    t = rotate(t, t->ch[0] ? t->ch[1] ? (t->ch[0]->pri < t->ch[1]->pri) : 1 : 0);
    t = erase(t, k);
  } else {
    int b = (k > cl);
    t->ch[b] = erase(t->ch[b], k - (b?cl+1:0));
  }
  t->cached = false;
  return t;
}
 
pair<node_t*, node_t*> split(node_t *t, int k) { // [0, k), [k, size)
  node_t *s = insert(t, k, val_t(), -1.0);
  return make_pair(s->ch[0], s->ch[1]); // memory leak
}
 
node_t *merge(node_t *l, node_t *r) {
  node_t *s = new node_t(val_t(), -1.0);
  s->ch[0] = l, s->ch[1] = r;
  return erase(s, count(l));
}



int N;
int rev[100010];

void print(node_t *p) {
  if (p == NULL) return;
  print(p->ch[0]);
  printf("%d ", rev[p->val]);
  print(p->ch[1]);
}

int main() {
  while (1 == scanf("%d", &N)) {
    node_t *root = NULL;
    
    rep (i, N) {
      int a, c;
      scanf("%d%d", &a, &c);
      rev[a] = i + 1;

      root = insert(root, i - c, a);
    }

    print(root);
    puts("");
  }
  
  return 0;
}

