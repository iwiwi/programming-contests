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
#include <limits.h>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

#define BEGIN_SOLVER struct solver {
#define END_SOLVER };

const int MAX_OUT = 10000;
const char *OUTPUT_FORMAT = "Case #%d: %s"; //"Case #%d:\n%s";

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;
const ll INF = 1LL << 60;


void init() {}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

struct segt {
  int n;
  vector<int> dat_sum, dat_max, dat_min;
  vector<bool> lazy_set;
  vector<int> lazy_val;

  void init(int n_) {
    for (n = 1; n < n_; n *= 2);
    dat_sum.clear(); dat_sum.resize(2 * n - 1, 0);
    dat_max.clear(); dat_max.resize(2 * n - 1, 0);
    dat_min.clear(); dat_min.resize(2 * n - 1, 0);
    lazy_set.clear(); lazy_set.resize(2 * n - 1, false);
    lazy_val.clear(); lazy_val.resize(2 * n - 1, false);
  }

  void eval_lazy(int k, int l, int r) {
    if (lazy_set[k]) {
      dat_sum[k] = (r - l) * lazy_val[k];
      dat_max[k] = dat_min[k] = lazy_val[k];
      if (r - l > 1) {
        lazy_val[k * 2 + 1] = lazy_val[k * 2 + 2] = lazy_val[k];
        lazy_set[k * 2 + 1] = lazy_set[k * 2 + 2] = true;
      }
    } else {
      dat_sum[k] += (r - l) * lazy_val[k];
      dat_max[k] += lazy_val[k];
      dat_min[k] += lazy_val[k];
      if (r - l > 1) {
        lazy_val[k * 2 + 1] += lazy_val[k];
        lazy_val[k * 2 + 2] += lazy_val[k];
      }
    }
    lazy_val[k] = 0;
    lazy_set[k] = false;
  }

  void query(int a, int b, int &rmax, int &rmin, int &rsum, int k = 0, int l = 0, int r = 0) {  // [a, b)
    if (k == 0) r = n;
    eval_lazy(k, l, r);
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      rmax = max(rmax, dat_max[k]);
      rmin = min(rmin, dat_min[k]);
      rsum += dat_sum[k];
    } else {
      query(a, b, rmax, rmin, rsum, k * 2 + 1, l, (l + r) / 2);
      query(a, b, rmax, rmin, rsum, k * 2 + 2, (l + r) / 2, r);
    }
  }

  int query_max(int a, int b) {
    int rmax, rmin, rsum;
    query(a, b, rmax, rmin, rsum);
    return rmax;
  }

  void query_add(int a, int b, int v, int k = 0, int l = 0, int r = 0) {  // [a, b)
    if (k == 0) r = n;
    eval_lazy(k, l, r);
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      lazy_val[k] += v;
      eval_lazy(k, l, r);
    } else {
      int lch = k * 2 + 1, rch = k * 2 + 2;
      query_add(a, b, v, lch, l, (l + r) / 2);
      query_add(a, b, v, rch, (l + r) / 2, r);
      dat_sum[k] = dat_sum[lch] + dat_sum[rch];
      dat_max[k] = max(dat_max[lch], dat_max[rch]);
      dat_min[k] = min(dat_min[lch], dat_min[rch]);
    }
  }

  void query_set(int a, int b, int v, int k = 0, int l = 0, int r = 0) {  // [a, b)
    if (k == 0) r = n;
    eval_lazy(k, l, r);
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      lazy_set[k] = true;
      lazy_val[k] = v;
      eval_lazy(k, l, r);
    }
    else {
      int lch = k * 2 + 1, rch = k * 2 + 2;
      query_set(a, b, v, lch, l, (l + r) / 2);
      query_set(a, b, v, rch, (l + r) / 2, r);
      dat_sum[k] = dat_sum[lch] + dat_sum[rch];
      dat_max[k] = max(dat_max[lch], dat_max[rch]);
      dat_min[k] = min(dat_min[lch], dat_min[rch]);
    }
  }
};
















int N, K;
ll X, A, B, M, p, q;

ll aa[300010], bb[300010], cc[300010], dd[300010];
ll X0[300010], X1[300010], Y0[300010], Y1[300010];

void input() {
  cin >> N >> K
      >> X >> A >> B >> M >> p >> q;

  rep (i, K) {
    cin >> aa[i] >> bb[i] >> cc[i] >> dd[i];
  }
}

ll prior;
long long next() {
  prior = (A * prior + B) % M;
  return prior;
}

void gen() {
  prior = X;
  for (int i = K; i < N; i++) {
    aa [i] = aa [i - K] + next() % (2 * p) - p;
    bb [i] = aa [i] + 1 + next() % (2 * (bb [i % K] - aa [i % K]));
    cc [i] = cc [i - K] + next() % (2 * q) - q;
    dd [i] = cc [i] + 1 + next() % (2 * (dd [i % K] - cc [i % K]));
  }
  for (int i = 0; i < N; i++) {
    X0 [i] = aa [i] * 1000000 + i;
    X1 [i] = bb [i] * 1000000 + i;
    Y0 [i] = cc [i] * 1000000 + i;
    Y1 [i] = dd [i] * 1000000 + i;
  }
}



int dp[300010];

void solve() {
  gen();
  rep (i, N) {
    assert(X0[i] < X1[i]);
    assert(Y0[i] < Y1[i]);
  }

  vector<ll> realY;
  rep (i, N) realY.push_back(Y0[i] / 1000000), realY.push_back(Y1[i] / 1000000);
  sort(all(realY));


  map<ll, int> ys;
  rep (i, N) ys[Y0[i]] = ys[Y1[i]] = 0;
  int YN = 0;
  tr (ys, ite) ite->second = YN++;
  rep (i, N) {
    Y0[i] = ys[Y0[i]];
    Y1[i] = ys[Y1[i]];
  }

  vector<pair<ll, int> > evt;
  rep (i, N) {
    evt.push_back(mp(X0[i], i));
    evt.push_back(mp(X1[i], i));
  }
  sort(all(evt));


  segt rmq;
  rmq.init(YN);

  int ln = 0, rn = N;
  ll ly = INF;
  priority_queue<pair<ll, int>, vector<pair<ll, int> >, less   <pair<ll, int> > > ryq;

  rep (i, N) {
    rmq.query_add(0, Y0[i], 1);
    ryq.push(mp(Y0[i], i));
  }


  int ans = 0;

  rep (ei, evt.size()) {
    ll x = evt[ei].first;
    int t = evt[ei].second;
    assert(0 <= t && t < N);

    // PROCESS [0, x), [x, inf)
    if (ln > 0 && rn > 0) {
      while (!ryq.empty()) {
        int z = ryq.top().second;
        if (X0[z] < x) ryq.pop();
        else break;
      }
      ll ry = ryq.top().first;
      ans = max(ans, rmq.query_max(ly, ry));
    }

    // UPDATE x
    if (X0[t] == x) {
      --rn;
      rmq.query_add(0, Y0[t], -1);
    } else {
      ++ln;
      ly = min(ly, Y1[t]);
      rmq.query_add(Y1[t], YN, 1);
    }
  }

  if (ans <= 1) puts("-1");
  else printf("%d\n", N - ans);
}










////////////////////////////////////////////////////////////////////////////////////////////////////
// Template
////////////////////////////////////////////////////////////////////////////////////////////////////

char out_buf[MAX_OUT], *out_p;

solver() : out_p(NULL) {}



void printf(const char* format, ...)
  __attribute__((format(printf, 2, 3)))
{
  if (!out_p) out_p = out_buf;

  va_list args;
  va_start(args, format);
  out_p += vsnprintf(out_p, sizeof(char) * (MAX_OUT - (out_p - out_buf)), format, args);
  va_end(args);

  if (out_p - out_buf >= MAX_OUT) {
    fprintf(stderr, "error: Output Limit Exceeded !!\n");
    exit(EXIT_FAILURE);
  }
}

void puts(const char *s) {
  printf("%s\n", s);
}

void debug(const char* format, ...)
  __attribute__((format(printf, 2, 3)))
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fflush(stderr);
}



END_SOLVER /////////////////////////////////////////////////////////////////////////////////////////



double sec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}



void print_status(int c, int C, double t0, double t1, int nth) {
  static const int L = 5;
  if (C > L && c % (C / L) != 0) return;
  else if (c - (nth - 1) / 2 <= 0) fprintf(stderr, "[ case: %d / %d ]\n", c, C);
  else {
    double t = sec();
    fprintf(stderr, "[ case: %d / %d | time: %.3f / %.3f ]\n",
            c, C, t - t0, (t1 - t0) + (t - t1) / (c - (nth - 1) / 2) * C);
  }
}



int main(int argc, char **argv) {
  bool parallel = false, status = false;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-p") == 0) parallel = status = true;
    else if (strcmp(argv[i], "-s") == 0) status = true;
    else {
      fprintf(stderr, "usage: %s [-p] [-s]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  double t0 = sec();
  init();
  double t1 = sec();
  if (status) fprintf(stderr, "[ init: %.3f ]\n", t1 - t0);

  string tmp;
  getline(cin, tmp);
  int C = atoi(tmp.c_str());

  if (!parallel) {
    if (status) fprintf(stderr, "[ mode: single thread ]\n");

    rep (c, C) {
      if (status) print_status(c, C, t0, t1, 1);

      solver *s = new solver();
      assert(s != NULL);
      s->input();
      s->solve();
      printf(OUTPUT_FORMAT, c + 1, s->out_buf);
      fflush(stdout);
      delete s;
    }
  }
  else {
#ifdef _OPENMP

    int nth = omp_get_max_threads();
    if (status) fprintf(stderr, "[ mode: parallel (%d) ]\n", nth);

    vector<string> out(C);
    vector<bool> done(C);
    int solve_c = 0, out_c = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);

#pragma omp parallel for schedule(dynamic, 1)
    rep (c, C) {
      solver *s = new solver();
      assert(s != NULL);

      int my_c;
      omp_set_lock(&lock);
      {
        while (out_c < C && done[out_c]) {
          printf(OUTPUT_FORMAT, out_c + 1, out[out_c].c_str());
          fflush(stdout);
          out_c++;
        }
        if (status) print_status(solve_c, C, t0, t1, nth);
        my_c = solve_c++;
        s->input();
      }
      omp_unset_lock(&lock);

      s->solve();

      omp_set_lock(&lock);
      {
        out[my_c] = string(s->out_buf);
        done[my_c] = true;
      }
      omp_unset_lock(&lock);
      delete s;
    }

    omp_destroy_lock(&lock);

    while (out_c < C) {
      assert(done[out_c]);
      printf(OUTPUT_FORMAT, out_c + 1, out[out_c].c_str());
      out_c++;
    }

#else
    fprintf(stderr, "error: compile with -fopenmp !!\n");
#endif
  }

  exit(EXIT_SUCCESS);
}
