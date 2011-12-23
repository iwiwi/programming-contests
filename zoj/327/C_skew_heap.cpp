#include <cstdio>
#include <climits>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
typedef int val_t;

struct node_t {
  val_t v;
  node_t *l, *r;
  node_t(val_t v) : v(v), l(NULL), r(NULL) {}
};

node_t *merge(node_t *x, node_t *y) {
  if (!x || !y) return x ? x : y;
  if (x->v < y->v) swap(x, y);
  x->r = merge(x->r, y);
  swap(x->l, x->r);
  return x;
}

node_t *add(node_t *x, val_t v) {
  return merge(x, new node_t(v));
}

node_t *pop(node_t *x) { // leak
  return merge(x->l, x->r);
}

val_t fst(node_t *p) {
  return p ? p->v : INT_MIN;
}


int main() {
  for (;;) {
    int N;
    scanf("%d", &N);
    if (N == 0) return 0;

    vector<int> A(N);
    for (int i = 0; i < N; ++i) scanf("%d", &A[i]);

    vector<int> nums;
    vector<node_t*> ques;
    for (int i = 0; i < N; ++i) {
      int x = A[i];

      node_t *q = add(NULL, x);
      int n = 1;
      while (!ques.empty() && fst(ques.back()) > fst(q)) {
	int qs = (nums.back() + 1) / 2 + (n + 1) / 2;
	n += nums.back();
	q = merge(ques.back(), q);
	nums.pop_back();
	ques.pop_back();
	for (; qs > (n + 1) / 2; --qs) q = pop(q);
      }
      nums.push_back(n);
      ques.push_back(q);
    }

    ll ans = 0;
    int j = 0;
    for (int i = 0; i < nums.size(); ++i) {
      int n = nums[i];
      int x = fst(ques[i]);
      for (int k = 0; k < n; ++k) {
	// printf("%d ", x);
	ans += abs(A[j++] - x);
      }
    }
    // puts("");
    cout << ans << endl;
  }
}
