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

#include <gmpxx.h>
typedef mpz_class bigint;
typedef mpq_class bigrat;


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

const ll MOD = 1000000000 + 7;
const int MAX_N = (1 << 25) + 10;
const int L = 40;
const int X = 40;


int prime[MAX_N], prime_n;
bool is_composite[MAX_N + 1];

void sieve(int n) {
  is_composite[0] = is_composite[1] = true;
  for (int i = 2; i * i <= n; i++) {
    if (is_composite[i]) continue;
    for (int j = i; i * j <= n; j++) is_composite[i * j] = true;
  }
  prime_n = 0;
  for (int i = 2; i <= n; i++) {
    if (!is_composite[i]) prime[prime_n++] = i;
  }
}

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}

ll pow_mod(ll a, ll k, ll m) {
  if (k == 0) return 1;
  ll t = pow_mod(a, k / 2, m);
  return mod(mod(t * t, m) * (k % 2 ? a : 1), m);
}


double logn[MAX_N];
ll prime_cmul[MAX_N];

void init() {
  sieve(MAX_N);
  for (int n = 1; n <= MAX_N; ++n) logn[n] = log(n);

  prime_cmul[0] = 1;
  rep (i, prime_n) prime_cmul[i + 1] = prime_cmul[i] * prime[i] % MOD;
}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

int B1, B2, A1, A2, C;

void input() {
  cin >> B1 >> B2 >> A1 >> A2 >> C;
}

ll lden[L];
ll N, D;

void multiply_num(ll n, ll r) {  // multiply |n^r| to the numerator
  rep (k, L) {
    ll p = prime[k];
    ll q = 0;
    while (n % p == 0) {
      q += r;
      n /= p;
    }

    ll gq = min(lden[k], q);
    lden[k] -= gq;
    N = N * pow_mod(p, q - gq, MOD) % MOD;

    if (n == 1) break;
  }
}

int compute_best_x(int p, int a, int b) {
  int best_x = 0;
  double best_v = 0.0;
  for (int x = 0; x <= X; ++x) {
    double v = logn[x + 1] * a - logn[p] * b * x;
    if (v > best_v) {
      best_x = x;
      best_v = v;
    }
  }
  return best_x;
}

void solve() {
  ll P = 0, Q = 0;

  for (ll b = B1; b <= B2; ++b) {
    for (ll a = A1; a <= A2; ++a) {
      if (a > C * b) continue;

      N = D = 1;

      // First |L| primes
      vector<ll> lnum;
      int last_x;
      for (int k = 0; k < L; ++k) {
        int p = prime[k];
        int best_x = compute_best_x(p, a, b);
        lnum.push_back(best_x + 1);
        lden[k] = best_x * b;
        last_x = best_x;
      }
      rep (k, L) multiply_num(lnum[k], a);
      rep (k, L) D = D * pow_mod(prime[k], lden[k], MOD) % MOD;

      // Remaining primes
      int i = L;
      for (int x = last_x; x >= 1; --x) {
        int lb = i - 1, ub = prime_n;
        while (ub - lb > 1) {
          int k = (lb + ub) / 2;
          int p = prime[k];

          double v1 = logn[x       + 1] * a - logn[p] * b * x;
          double v2 = logn[(x - 1) + 1] * a - logn[p] * b * (x - 1);
          if (v2 > v1) ub = k;
          else lb = k;
        }
        int j = ub;  // |x| is the best x for [i, j)

        multiply_num(x + 1, (j - i) * a);
        ll t = prime_cmul[j] % MOD * inverse(prime_cmul[i], MOD) % MOD;
        D = D * pow_mod(t, b * x, MOD) % MOD;

        i = j;
      }

      P += N;
      Q += D;
    }
  }

  printf("%lld %lld\n", P, Q);
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
