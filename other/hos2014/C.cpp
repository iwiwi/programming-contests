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

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

#define BEGIN_SOLVER struct solver {
#define END_SOLVER };

const int MAX_OUT = 10000;
const char *OUTPUT_FORMAT = "%s"; //"Case #%d:\n%s";

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair


typedef long long ll;
const ll MOD = 2014122419;



typedef ll val_t;
typedef vector<val_t> poly_t;

#define NOR(x) ((x) % MOD)

poly_t poly_pow(const poly_t &a, ll k) {
  int n = a.size() - 1;
  poly_t p(n + 1), q(n * 2);
  p[0] = 1;
  for (int s = sizeof(ll) * 8 - __builtin_clzll(k) - 1; s >= 0; s--) {
    rep (i, n * 2) q[i] = 0;
    val_t r = p[n];
    int d = (k >> s) & 1;
    rep (i, n) {
      rep (j, n) q[i + j + d] = NOR(q[i + j + d] + p[i] * p[j]);
      r = NOR(r + p[i] * p[n]);
    }
    for (int i = 2 * n - 1; i >= n; i--) {
      rep (j, n) q[i - n + j] = NOR(q[i - n + j] + q[i] * a[j]);
      r = NOR(r + q[i] * a[n]);
    }
    rep (i, n) p[i] = q[i];
    p[n] = r;
  }
  return p;
}



typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS0(x) ((x) == 0)
#define INV(x) inverse(x, MOD)
#define NOR(x) ((x) % MOD)

inline ll inverse(ll a, ll m){
  ll b = m, u = 1, v = 0;
  while (b) {
    ll t = a / b;
    swap(a -= t * b, b);
    swap(u -= t * v, v);
  }
  return (u % m + m) % m;
}

vec_t gauss_jordan(mat_t A, const vec_t &b) {
  int m = A.size(), n = A[0].size(); // m(tate) x n(yoko)
  for (int i = 0; i < m; i++) A[i].resize(n + 1, b[i]);

  int pi = 0;
  for (int pj = 0; pj < n && pi < m; pj++) {
    for (int i = pi + 1; i < m; i++) if (ABS(A[pi][pj]) < ABS(A[i][pj])) swap(A[pi], A[i]);
    if (IS0(A[pi][pj])) continue;
    for (int j = n; j >= pj; j--) A[pi][j] = NOR(A[pi][j] * INV(A[pi][pj]));
    for (int i = 0; i < m; i++)
      if (i != pi) for (int j = n; j >= pj; j--) A[i][j] = NOR(A[i][j] - A[i][pj] * A[pi][j]);
    pi++;
  }

  vec_t x(n, 0);
  for (int i = 0; i < m; i++) {
    int j;
    for (j = 0; j < n; j++) if (!IS0(A[i][j])) break;
    if (j == n && !IS0(A[i][n])) return vec_t();
    else if (j < n) x[j] = A[i][n];
  }
  return x;
}

mat_t identity(int n) {
  mat_t A(n, vec_t(n));
  for (int i = 0; i < n; i++) A[i][i] = 1;
  return A;
}

mat_t multiply(const mat_t &A, const mat_t &B) {
  mat_t C(A.size(), vec_t(B[0].size()));
  #pragma omp parallel for
  rep (i, C.size())
      rep (k, A[i].size()) rep (j, C[i].size()) {
    C[i][j] = NOR(C[i][j] + A[i][k] * B[k][j]);
  }
  return C;
}

mat_t power(const mat_t &A, long long p) {
  if (p == 0) return identity(A.size());
  if (p == 1) return A;
  mat_t B = power(multiply(A, A), p / 2);
  if (p % 2 == 1) B = multiply(B, A);
  return B;
}

vec_t multiply(const mat_t &A, const vec_t &x) {
  vec_t y(A.size());
  rep (i, A.size()) rep (j, A[i].size()) y[i] = NOR(y[i] + A[i][j] * x[j]);
  return y;
}

poly_t get_poly(const mat_t &A) {
  int n = A.size();
  vec_t x(n);
  rep (i, n) x[i] = rand() % MOD;

  mat_t B;
  rep (i, n) {
    B.emplace_back(x);
    x = multiply(A, x);
  }

  vec_t y = gauss_jordan(B, x);

  poly_t p = y;
  p.emplace_back(0);
}

mat_t super_power(const mat_t &A, long long k) {
  poly_t p = get_poly(A);
  p = poly_pow(p, k);
}



void init() {}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

int N, M;
mat_t A;

void input() {
  scanf("%d%d", &N, &M);
  A.assign(N, vec_t(N, 0));

  rep (i, M) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a;
    --b;
    A[a][b] += 1;
  }

  debug("%d %d\n", N, M);
}


void solve() {
  vector<int> id(N), od(N);
  rep (i, N) rep (j, N) id[i] += A[i][j];
  rep (i, N) rep (j, N) od[j] += A[i][j];

  int t = 0, e = 0;
  rep (i, N) rep (j, N) if (id[i] && od[i] && id[j] && od[j]) e += A[i][j];
  debug("%d\n", e);
  return;

  A = power(A, MOD);

  ll ans = 0;
  rep (i, N) {
    (ans += A[i][i]) %= MOD;
  }
  printf("%lld\n", ans);
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
      printf(OUTPUT_FORMAT, s->out_buf);
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
          printf(OUTPUT_FORMAT, out[out_c].c_str());
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
      printf(OUTPUT_FORMAT, out[out_c].c_str());
      out_c++;
    }

#else
    fprintf(stderr, "error: compile with -fopenmp !!\n");
#endif
  }

  exit(EXIT_SUCCESS);
}
