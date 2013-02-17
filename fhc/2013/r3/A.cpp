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

const ll MOD = (1E9) +7;

typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS0(x) ((x) == 0)
#define INV(x) inverse(x, MOD)
#define NOR(x) ((x) % MOD)

mat_t identity(int n) {
  mat_t A(n, vec_t(n));
  for (int i = 0; i < n; i++) A[i][i] = 1;
  return A;
}

mat_t multiply(const mat_t &A, const mat_t &B) {
  mat_t C(A.size(), vec_t(B[0].size()));
  rep (i, C.size()) rep (k, A[i].size()) rep (j, C[i].size()) {
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

mat_t power_sum(const mat_t &A, long long p) {
  int n = A.size();

  mat_t B(n * 2, vec_t(n * 2));
  rep (i, n) rep (j, n) B[i][j] = A[i][j];
  rep (i, n) B[i][n + i] = B[n + i][n + i] = 1;

  B = power(B, p + 1);

  mat_t C(n, vec_t(n));
  rep (i, n) rep (j, n) C[i][j] = B[i][n + j];
  return C;
}




void init() {}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

ll K;
bool war[20][20];
int L;

void input() {
  cin >> K;
  rep (a, 10) rep (b, 10) cin >> war[a][b];
}

int id(int p2, int p1) {
  return p2 * 11 + p1;
}

void solve() {
  int S = 11 * 11;
  mat_t A(S, vec_t(S));
  A[id(10, 10)][id(10, 10)] += 1;
  for (int p0 = 1; p0 <= 9; ++p0) {
    A[id(10, 10)][id(10, p0)] += 1;
  }
  for (int p1 = 1; p1 <= 9; ++p1) {
    rep (p0, 10) {
      if (war[p1][p0]) continue;
      A[id(10, p1)][id(p1, p0)] += 1;
    }
  }
  rep (p2, 10) rep (p1, 10) rep (p0, 10) {
    if (war[p2][p0] || war[p1][p0]) continue;
    A[id(p2, p1)][id(p1, p0)] += 1;
  }

  A = power(A, K);

  ll ans = 0;
  rep (p2, 11) rep (p1, 10) (ans += A[id(10, 10)][id(p2, p1)]) %= MOD;
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
