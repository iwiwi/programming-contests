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
typedef long double ld;


void init() {}



const double gr = 2 / (3 + sqrt(5));
const int iter_n = 10000;
const int trial = 20000000;


BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////




ll M, F, N;
vector<pair<ll, ll> > A;

void input() {
  cin >> M >> F >> N;
  A.resize(N);
  rep (i, N) cin >> A[i].first >> A[i].second;
}

ld f(ld buy) {
  ld res = 0;

  ld money = M / buy - F;
  ll day = 0;

  rep (i, A.size()) {
    ld p = A[i].first;
    ld lim = A[i].second - day + 1;
    ld x = min(lim, money / p);
    res += buy * x;
    money -= x * p;
    day = A[i].second + 1;
  }

  return res;
}

ld golden(ld l, ld r) {
  ld ml = l + gr * (r - l), mr = r - gr * (r - l);
  ld fml = f(ml), fmr = f(mr);
  for (int iter = 0; iter < iter_n; iter++) {
    if (fml < fmr) {
      l = ml;
      ml = mr;
      mr = r - gr * (r - l);
      fml = fmr;
      fmr = f(mr);
    }
    else {
      r = mr;
      mr = ml;
      ml = l + gr * (r - l);
      fmr = fml;
      fml = f(ml);
    }
  }
  return ml;
}

ll g(ll buy) {
  if (F * (ld)buy > M) return 0;

  ll res = 0;

  ll money = M - F * buy;
  ll day = 0;

  rep (i, A.size()) {
    ll p = A[i].first;
    ll lim = A[i].second - day + 1;

    if (lim * (ld)p * buy > money) {
      return res + (money / p);
    }

    res += lim * buy;
    money -= lim * buy * p;
    day = A[i].second + 1;
  }

  return res;
}

void solve() {
  sort(all(A));
  rep (i, A.size()) {
    if (i == 0) continue;
    if (A[i - 1].second > A[i].second) {
      A.erase(A.begin() + i);
      --i;
    }
  }

  ld buy = golden((ld)1, M / (ld)F);

  ll ans = 0;
  ll ans_buy = 0;
  ll t = buy;
  for (ll a = max(1LL, t - trial); a <= t + trial; ++a) {
    ll t = g(a);
    if (t > ans) {
      ans = t;
      ans_buy = a;
    }
  }

  /*
  // small
  ll ans = 0;
  for (ll buy = 1; buy <= M / F; ++buy) ans = max(ans, g(buy));
  */

  printf("%lld\n", ans);
  // debug("%lld (%lld) --- %Lf (%Lf, %lld) -> %Lf\n", ans, ans_buy, f(buy), buy, t, buy - ans_buy);
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
