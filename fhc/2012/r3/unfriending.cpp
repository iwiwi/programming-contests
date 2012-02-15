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



void init() {}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

int N, M;
int X[50010];
vector<int> Y[1510];

void input() {
  cin >> N >> M;
  {
    ll X0, A, B, P;
    cin >> X0 >> A >> B >> P;
    X[0] = X0;
    for (int i = 1; i < N; ++i) {
      X[i] = (X[i - 1] * A + B) % P;
    }
  }
  rep (i, M) {
    ll size, Y0, A, B;
    cin >> size >> Y0 >> A >> B;
    Y[i].resize(size);
    Y[i][0] = Y0;
    for (int j = 1; j < size; ++j) {
      Y[i][j] = (Y[i][j - 1] * A + B) % N;
    }
    sort(all(Y[i]));
    Y[i].erase(unique(all(Y[i])), Y[i].end());
  }
}

vector<int> belong[50010];
int use[50010];
vector<int> edit;
int D;

bool search(int k, int v) {
  if (use[k] != -1) return use[k] == v;
  use[k] = v;
  edit.pb(k);

  if (v == 1) {
    int cnt = 0;
    for (int i = upper_bound(X, X + N, X[k] - D) - X;
         i < N && X[i] < X[k] + D; ++i)
    {
      if (i == k) continue;
      ++cnt;
      if (!search(i, 0)) return false;
    }
  }
  else {
    if (belong[k].empty()) return false;

    rep (i, belong[k].size()) {
      int l = belong[k][i];
      rep (j, Y[l].size()) {
        int y = Y[l][j];
        if (y == k) continue;
        if (!search(y, 1)) return false;
      }
    }
  }

  return true;
}

bool test(int k, int v) {
  edit.clear();
  if (search(k, v)) return true;
  else {
    rep (i, edit.size()) use[edit[i]] = -1;   // Revert
    return false;
  }
}

void solve() {
  // Arrange data
  rep (i, M) rep (j, Y[i].size()) Y[i][j] = X[Y[i][j]];
  sort(X, X + N);
  N = unique(X, X + N) - X;
  rep (i, M) {
    rep (j, Y[i].size()) {
      int y = Y[i][j];
      int k = lower_bound(X, X + N, y) - X;
      belong[k].pb(i);
      Y[i][j] = k;
    }
  }

  // Binary search
  int lb = 0, ub = (1 << 30) + 10;
  while (ub - lb > 1) {
    D = lb + (ub - lb) / 2;
    memset(use, -1, sizeof(use));

    rep (i, N) {
      if (!test(i, 1) && !test(i, 0)) {
        goto ng;
      }
    }

    // Success
    lb = D;
    continue;
 ng:
    // Fail
    ub = D;
  }

  printf("%d\n", lb);
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
