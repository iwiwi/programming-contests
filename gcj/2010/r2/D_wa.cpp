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

#include <complex>
const double EPS = 1e-10;
typedef complex<double> p_t;

namespace std {
  istream &operator>>(istream &is, p_t &p) {
    is >> p.real() >> p.imag();
    return is;
  }
}

double hoge(double r1, double r2, double d) {

    double a = (r1 * r1 - r2 * r2 + d * d) / d / 2.;
    double h = sqrt(max(0., r1 * r1 - a * a));
    double alpha = atan2(h, a);
    printf(" %f\n", alpha);
    return alpha * r1 * r1 - a * h;
}

double area_cc(double r1, double r2, double d) {
  if (r1 + r2 < d + EPS) return 0.0;
  else if (d < fabs(r1 - r2) + EPS) {
    double r = min(r1, r2);
    return r * r * M_PI;
  }
  else {
    double x = (d * d + r1 * r1 - r2 * r2) / d / 2.0;
    double h = sqrt(max(0.0, r1 * r1 - x * x));
    return r1 * r1 * atan2(h, x) + r2 * r2 * atan2(h, d - x) - d * h;
  }
}




void init() {}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

int N, M;
p_t P[2], Q[20];

void input() {
  cin >> N >> M;
  assert(N == 2);
  rep (i, N) cin >> P[i];
  rep (i, M) cin >> Q[i];
}


inline double sqr(double x) { return x * x; }

void solve() {
  rep (m, M) {
    // cout << P[0] << P[1] << Q[m] << endl;
    const p_t &q = Q[m];

    double r[2];
    rep (i, 2) r[i] = abs(P[i] - q);

    double d = abs(P[1] - P[0]);
    ///*
    double ans = area_cc(r[0], r[1], d);
    /*/

    double lx = max(P[0].real() - r[0], P[1].real() - r[1]);
    double rx = min(P[0].real() + r[0], P[1].real() + r[1]);

    const int ITER = 80000000;
    double s = 0.0;
    rep (i, ITER) {
      double x = lx + (rx - lx) / ITER * i;

      double dy0 = sqrt(sqr(r[0]) - sqr(P[0].real() - x));
      double dy1 = sqrt(sqr(r[1]) - sqr(P[1].real() - x));

      double ymi = max(P[0].imag() - dy0, P[1].imag() - dy1);
      double yma = min(P[0].imag() + dy0, P[1].imag() + dy1);
      s += max(0.0, yma - ymi);
    }

    double ans = s * (rx - lx) / ITER;
    */

    printf("%.10f%c", ans, m == M - 1 ? '\n' : ' ');
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

      out[my_c] = string(s->out_buf);
      done[my_c] = true;
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
