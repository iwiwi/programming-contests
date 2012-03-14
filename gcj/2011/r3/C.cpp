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

typedef double number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;
const double EPS = 1E-10;

#define ABS(x) (fabs(x))
#define IS0(x) (fabs(x) < EPS)
#define INV(x) (1 / (x))
#define NOR(x) (x)

const ll MOD = 1000003;

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

int rank(mat_t A) {
  int n = A[0].size(), m = A.size(), i, j, k, r = 0;
  for (i = 0; i < n && r < m; i++) {
    int piv = r;
    for (j = r + 1; j < m; j++)
      if (ABS(A[j][i]) > ABS(A[piv][i])) piv = j;
    swap(A[r], A[piv]);

    if (IS0((A[r][i]))) continue;

    for (j = r + 1; j < m; j++)
      for (k = n - 1; k >= i; k--)
        A[j][k] -= A[r][k] * A[j][i] / A[r][i];

    r++;
  }
  return r;
}



pair<int, int> dxy[300];

void init() {
  dxy['-']  = mp(-1, 0);
  dxy['|']  = mp(0, -1);
  dxy['/']  = mp(-1, 1);
  dxy['\\'] = mp(1, 1);
}


typedef vector<map<int, double> > smat_t;

int rank(smat_t A) {
  int n = A.size(), r = 0;
  rep (i, n) {
    vector<int> zero;
    tr (A[i], ite) {
      if (IS0(ite->second)) zero.pb(ite->first);
    }
    rep (j, zero.size()) A[i].erase(zero[j]);
    if (A[i].empty()) continue;
    ++r;

    int k = A[i].begin()->first;
    for (int j = i + 1; j < n; ++j) {
      if (A[j].count(k)) {
        double r = A[j][k] / A[i][k];
        tr (A[i], ite) {
          int l = ite->first;
          A[j][l] -= r * ite->second;
          if (IS0(A[j][l])) A[j].erase(l);
        }
      }
    }
  }
  return r;
}


BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

int H, W;
char fld[110][110];

void input() {
  scanf("%d%d", &H, &W);
  rep (y, H) rep (x, W) scanf(" %c", &fld[y][x]);
}

int id(int x, int y) {
  return y * W + x;
}

void solve() {
  int N = W * H;
  smat_t A(N), B(N);

  rep (i, N) B[i][N] = 1;

  rep (y, H) {
    rep (x, W) {
      int v = id(x, y);

      int tx1 = (x + dxy[fld[y][x]].first  + W) % W;
      int ty1 = (y + dxy[fld[y][x]].second + H) % H;
      int tv1 = id(tx1, ty1);
      --B[tv1][N];

      int tx2 = (x - dxy[fld[y][x]].first  + W) % W;
      int ty2 = (y - dxy[fld[y][x]].second + H) % H;
      int tv2 = id(tx2, ty2);

      A[tv1][v] += -1; B[tv1][v] += -1;
      A[tv2][v] +=  1; B[tv2][v] +=  1;
    }
  }

  // rep (i, N) rep (j, N) debug("%.f ", A[i][j]); debug("%.f\n", b[i]);

  int ra = rank(A);
  int rb = rank(B);

  debug("%d %d\n", ra, rb);

  if (ra != rb) {
    puts("0");
  } else {
    int r = ra;

    ll ans = 1;
    rep (i, N - r) {
      ans *= 2;
      ans %= MOD;
    }
    printf("%lld\n", ans);
  }
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
