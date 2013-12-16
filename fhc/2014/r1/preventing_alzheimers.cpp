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

const int INF = 987654321;
const int MAX_N = 1000010;

vector<int> factor[MAX_N + 1];

void factorize_all(int n) {
  static int rest[MAX_N + 1];
  for (int i = 2; i <= n; i++) {
    rest[i] = i;
    factor[i].clear();
  }
  for (int i = 2; i * i <= n; i++) {
    if (factor[i].size() != 0) continue;
    for (int j = i; i * j <= n; j++) {
      int t = i * j, c = 0;
      while (rest[t] % i == 0) {
        c++;
        rest[t] /= i;
      }
      factor[t].push_back(i);
    }
  }
  for (int i = 2; i <= n; i++) {
    if (rest[i] != 1) factor[i].push_back(rest[i]);
  }

  for (int x = 1; x <= 1000; ++x) {  // ZERO!
    if (factor[x].size() == 1) factor[0].pb(x);
  }
}

void init() {
  factorize_all(MAX_N);
}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

int N, K;
int A[30], B[30];

void input() {
  cin >> N >> K;
  rep (i, N) cin >> A[i];
}

int ans_naive;

void search_naive(int k) {
  int s = accumulate(B, B + k, 0);
  if (s >= ans_naive) return;

  if (k == N) {
    ans_naive = s;
  } else {
    for (int x = A[k]; x <= 10000; ++x) {
      rep (i, k) if (__gcd(B[i], x) != K) goto dmp;
      B[k] = x;
      search_naive(k + 1);
   dmp:;
    }
  }
}

int solve_naive() {
  ans_naive = INF;
  search_naive(0);
  return ans_naive - accumulate(A, A + N, 0);
}

map<vector<int>, int> mem[30];

int search(int k, const vector<int> &u) {
  if (k == N) return 0;
  if (mem[k].count(u)) return mem[k][u];
  int ans = INF;

  for (int x = B[k]; ; ++x) {
    vector<int> tu(u);
    tu.insert(tu.end(), all(factor[x]));
    sort(all(tu));
    if (unique(all(tu)) != tu.end()) continue;  // gcd != 1

    ans = min(ans, x + search(k + 1, tu));

    if (x > B[N - 1] && factor[x].size() == 1) break;
  }

  return mem[k][u] = ans;
}

void solve() {
  rep (i, N) B[i] = A[i] / K + (A[i] % K ? 1 : 0);
  sort(B, B + N);

  int r = search(0, {});
  int a = r * K - accumulate(A, A + N, 0);

  if (false) {
    int b = solve_naive();
    debug("K = %d, A = ", K);
    rep (i, N) debug("%d ", A[i]);
    debug("\t-> %d vs %d\n", a, b);
    assert(a == b);
  }

  printf("%d\n", a);
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
