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

typedef int val_t;
typedef long long ll;


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



struct range_tree {
  int n;
  vector<multimap<int, val_t> > dat;
  vector<vector<pair<int, val_t> > > pre;

  range_tree(int n_) {
    for (n = 1; n < n_; n *= 2);
    dat.resize(n*2-1);
    pre.resize(n*2-1);
  }

  void insert(int x, int y, const val_t &v) {
    int k = x + n-1;
    //dat[k].insert(mp(y, v));
    pre[k].pb(mp(y, v));
    while (k > 0) {
      // dat[k = (k-1)/2].insert(mp(y, v));
      pre[k = (k-1)/2].pb(mp(y, v));
    }
  }

  void insert(int k, int l, int r, int *xs, int *ys, int n) {
    if (l == r) return;

    int m = (l + r) / 2;

    dat[k].insert(ys, ys + n);

    int first = 0, last = n;
    while (true)
    {
      while (first!=last && xs[first] < m) ++first;
      if (first==last--) break;
      while (first!=last && xs[last] >= m) --last;
      if (first==last) break;
      swap(xs[first++],xs[last]);
      swap(ys[first++],ys[last]);
    }

    insert(k * 2 + 1, l, m, xs, ys, first);
    insert(k * 2 + 2, m, r, xs + first, ys + first, n - first);
  }

  void construct() {
    rep (i, dat.size()) dat[i].insert(pre[i].begin(), pre[i].end());
  }

  // [xlb, xub) * [ylb, yub)
  void query(int xlb, int xub, int ylb, int yub, vector<val_t> &vs,
             int k = 0, int l = 0, int r = 0) {
    if (k == 0) r = n;
    if (r <= xlb || xub <= l) return;
    if (xlb <= l && r <= xub) {
      iter(dat[k]) ilb = dat[k].lower_bound(ylb), iub = dat[k].lower_bound(yub);
      for (iter(dat[k]) ite = ilb; ite != iub; ++ite) vs.pb(ite->second);
      dat[k].erase(ilb, iub); // DELETEEEEEEEEEEE !!
    } else {
      query(xlb, xub, ylb, yub, vs, k*2+1, l, (l+r)/2);
      query(xlb, xub, ylb, yub, vs, k*2+2, (l+r)/2, r);
    }
  }
};

range_tree rtree(0);
map<ll, int> rx2sx;

int N;
ll D[1000010];
int M[1000010], P[1000010], R[1000010];

int xs2[1000010];

void construct(ll *xs, int *ys) {
  rx2sx.clear();
  rep (i, N) rx2sx[xs[i]] = 0;
  int n = 0;
  tr (rx2sx, ite) ite->second = n++;
  rx2sx[ll(1E20)] = n;
  rtree = range_tree(n);

  rep (i, N) xs2[i] = rx2sx[i];;
  rtree.insert(0, 0, rtree.n, (int*)xs2, ys, N);

  // benchmark("insert")
  // rep (i, N) rtree.insert(rx2sx[xs[i]], ys[i], i);

  benchmark("construct")
  rtree.construct();
}

void query(ll xlb, ll xub, int ylb, int yub, vector<val_t> &vs) {
  rtree.query(rx2sx.lower_bound(xlb)->second, rx2sx.lower_bound(xub)->second, ylb, yub, vs);
}

int pop;

int ans;
bool done[1000010];
queue<int> que;

void process(int p, ll r) {
  vector<int> vs;
  query(0, r * r + 1, 0, p + 1, vs);
  rep (i, vs.size()) {
    ++pop;

    int k = vs[i];
    if (done[k]) continue;
    ++ans;
    que.push(k);
    done[k] = true;
  }
}

int main() {
  int X0, Y0, P0, R0;
  while (scanf("%d%d%d%d%d", &X0, &Y0, &P0, &R0, &N) == 5) {
    rep (i, N) {
      int x, y;
      scanf("%d%d%d%d%d", &x, &y, M + i, P + i, R + i);
      D[i] = ll(x - X0) * (x - X0) + ll(y - Y0) * (y - Y0);
    }

    //!!!
    N = 250000;
    rep (i, N) {
      D[i] = rand() * ll(rand());
      M[i] = rand();
      P[i] = rand();
      R[i] = rand();
    }

    benchmark("construct")
    construct(D, M);

    ans = 0;
    memset(done, 0, sizeof(done));

    benchmark("process"){
    process(P0, R0);

    while (!que.empty()) {
      int k = que.front();
      // fprintf(stderr, "k = %d\n", k);
      que.pop();
      process(P[k], R[k]);
    }
    }

    fprintf(stderr, "!!! %d !!!\n", pop);

    printf("%d\n", ans);
  }

  return 0;
}

