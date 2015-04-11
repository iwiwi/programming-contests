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
#include <functional>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

template<class T = int>
class fenwick_tree {
 public:
  fenwick_tree(size_t n) : a_(n) {}

  size_t size() {
    return a_.size();
  }

  void add(size_t i, T x) {
    for (; i < a_.size(); i |= i + 1) a_[i] += x;
  }

  T sum(size_t i) {  // [0, i)
    T s = 0;
    for (; i > 0; i = (i & (i - 1))) s += a_[i - 1];
    return s;
  }

  size_t lower_bound(T s) {  // sum [0, i) < s && sum [0, i] >= s
    size_t k = 1;
    while (k * 2 <= a_.size()) k *= 2;

    size_t i = 0;
    T t = T();
    for (; k > 0; k /= 2) {
      if (i + k <= a_.size() && t + a_[i + k - 1] < s) {
        t += a_[i + k - 1];
        i += k;
      }
    }

    return i;
  }

 private:
  vector<T> a_;
};

template<typename T>
class segment_tree {
 public:
  segment_tree(size_t n) {
    n_ = 1;
    while (n_ < n) n_ <<= 1;
    data_.resize(n_ * 2);
    bulk_update();
  }

  void bulk_update() {
    for (size_t i = n_ - 1; i-- != 0; ) {
      assert(i * 2 + 2 < data_.size());
      data_[i] = data_[i * 2 + 1] + data_[i * 2 + 2];
    }
    is_dirty_ = false;
  }

  T &leaf(size_t i) {
    is_dirty_ = true;
    return data_[i + n_ - 1];
  }

  void leaf(size_t i, std::function<void(T&)> f) {
    f(data_[i + n_ - 1]);
    update(i);
  }

  T root() {
    assert(!is_dirty_);
    return data_[0];
  }

  T query(int l, int r) {
    assert(!is_dirty_);
    return query_rec(l, r, 0, 0, n_);
  }

  size_t size() {
    return n_;
  }

 private:
  size_t n_;
  vector<T> data_;
  bool is_dirty_;

  T query_rec(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return T();
    if (a <= l && r <= b) return data_[k];
    else return
             query_rec(a, b, k * 2 + 1, l, (l + r) / 2) +
             query_rec(a, b, k * 2 + 2, (l + r) / 2, r);
  }

  void update(size_t i) {
    i += n_ - 1;
    while (i > 0) {
      i = (i - 1) / 2;
      data_[i] = data_[i * 2 + 1] + data_[i * 2 + 2];
    }
  }
};

struct node {
  ll xmin, xmax, num, sum;
  node() : xmin(INT_MAX), xmax(INT_MIN), num(0), sum(0) {}
};

node operator+(const node &l, const node &r) {
  node n;
  n.xmin = min(l.xmin, r.xmin);
  n.xmax = max(l.xmax, r.xmax);
  n.num = l.num + r.num;
  n.sum = l.sum + r.sum;
  return n;
}

const int A = 200005;

struct color_t {
  set<int> xs;
  color_t() {}
  int xmin() { return xs.empty() ? INT_MAX : *xs.begin(); }
  int xmax() { return xs.empty() ? INT_MIN : *--xs.end(); }
} cs[200010];

map<int, int> x2a;
fenwick_tree<int> ft(A);
segment_tree<node> st(A);

void update_color(int a) {
  st.leaf(a, [=](node &n) {
      n.xmin = cs[a].xmin();
      n.xmax = cs[a].xmax();
      n.num = cs[a].xs.size();
      n.sum = cs[a].xs.size() * (ll)a;
    });
}

ll solve(int a) {
  node l = st.query(0, a), r = st.query(a + 1, A);
  ll xmin = -min({0LL, l.xmin, r.xmin}), xmax = max({0LL, l.xmax, r.xmax});
  ll xcost = min(xmin, xmax) * 2 + max(xmin, xmax);
  ll acost = (l.num * a - l.sum) + (r.sum - r.num * a);
  return xcost + acost;
}

int main() {
  set<int> as;

  int N;
  scanf("%d", &N);
  rep (i, N) {
    int x, a;
    scanf("%d%d", &x, &a);
    cs[a].xs.insert(x);
    x2a[x] = a;
    ft.add(a, 1);
    as.insert(a);
  }

  rep (a, A) update_color(a);

  int Q;
  scanf("%d", &Q);
  while (Q--) {
    int c, x, a;
    scanf("%d%d%d", &c, &x, &a);
    as.insert(a);

    if (c == 1) {
      cs[a].xs.insert(x);
      x2a[x] = a;
      ft.add(a, 1);
    } else {
      cs[a].xs.erase(x);
      x2a.erase(x);
      ft.add(a, -1);
    }
    update_color(a);

    ll s1 = solve(x2a[st.root().xmin]);
    ll s2 = solve(x2a[st.root().xmax]);
    ll s3 = solve(ft.lower_bound((x2a.size() + 1) / 2));
    printf("%lld\n", min({s1, s2, s3}));
  }
}
