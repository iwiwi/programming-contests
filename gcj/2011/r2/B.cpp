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

const double EPS = 1E-10;

void init() {}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

int H, W, D;
int fld[1010][1010];

void input() {
  scanf("%d%d%d", &H, &W, &D);
  memset(fld, 0, sizeof(fld));
  rep (y, H) rep (x, W) {
    char c;
    scanf(" %c", &c);
    fld[y * 2][x * 2] = c - '0';
  }
  H *= 2;
  W *= 2;
}

double wh[1010][1010];
double wv[1010][1010];
double sh[1010][1010];
double sv[1010][1010];

void solve() {
  int ans = 0;

  rep (x, W) {
    rep (y, H) wh[x][y + 1] = wh[x][y] + y * fld[y][x];
    rep (y, H) sh[x][y + 1] = sh[x][y] + fld[y][x];
  }
  rep (y, H) {
    rep (x, W) wv[x + 1][y] = wv[x][y] + x * fld[y][x];
    rep (x, W) sv[x + 1][y] = sv[x][y] + fld[y][x];
  }

  // only consider the odd case
  rep (x, W) rep (y, H) {
    if (x % 2 != y % 2) continue;

    double sx = 0.0, sy = 0.0;
    for (int n = 0; ; ++n) {
      if (fabs(sx) < EPS && fabs(sy) < EPS) {
        if (x % 2 == 0 && n % 2 == 0) ans = max(ans, n + 1);
        if (x % 2 == 1 && n % 2 == 1) ans = max(ans, n + 1);
        // printf("%d %d\n", x, y);
      }

      // corner
      for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
          int tx = x + dx * n;
          int ty = y + dy * n;
          if (tx < 0 || W <= tx || ty < 0 || H <= ty) goto out;
          sx += (tx - x) * fld[ty][tx];
          sy += (ty - y) * fld[ty][tx];
        }
      }

      // line
      /*
      for (int rx = -1; rx <= 1; rx += 2) {
        int tx = x + rx * (n + 1);
        for (int ty = y - n + 1; ty <= y + n - 1; ++ty) {
          if (tx < 0 || W <= tx || ty < 0 || H <= ty) goto out;
          sx += (tx - x) * fld[ty][tx];
          sy += (ty - y) * fld[ty][tx];
        }
      }
      for (int ry = -1; ry <= 1; ry += 2) {
        int ty = y + ry * (n + 1);
        for (int tx = x - n + 1; tx <= x + n - 1; ++tx) {
          if (tx < 0 || W <= tx || ty < 0 || H <= ty) goto out;
          sx += (tx - x) * fld[ty][tx];
          sy += (ty - y) * fld[ty][tx];
        }
      }
      */
      for (int rx = -1; rx <= 1; rx += 2) {
        int tx = x + rx * (n + 1);

      }
    }
 out:;
  }

  if (ans < 3) puts("IMPOSSIBLE");
  else printf("%d\n", ans);
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
