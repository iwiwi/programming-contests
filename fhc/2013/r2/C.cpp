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

const ll MOD = 1000000007;

ll cmb[1100][1100];

void init_cmb(int N) {
  cmb[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    cmb[i][0] = 1;
    for (int j = 1; j <= i; ++j) cmb[i][j] = (cmb[i-1][j-1] + cmb[i-1][j]) % MOD;
  }
}

void init() {
  init_cmb(1010);
}

enum SIGN { LT, GT };

BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

int N;
vector<pair<int, SIGN> > adj[1010];

void input() {
  scanf("%d", &N);
  rep (i, N - 1) {
    char sign[256];
    int a, b;
    scanf("%d %s %d", &a, sign, &b);
    if (sign[0] == '>') swap(a, b);
    // a < b

    adj[a].pb(mp(b, LT));
    adj[b].pb(mp(a, GT));
  }
}

ll naive() {
  ll ans = 0;

  vector<int> ord(N);
  rep (i, N) ord[i] = i;
  do {
    vector<int> pos(N);
    rep (i, N) pos[ord[i]] = i;

    rep (i, N) rep (j, adj[i].size()) {
      if ((pos[i] < pos[adj[i][j].first]) != (adj[i][j].second == LT)) goto ng;
    }
    ++ans;
 ng:;
  } while (next_permutation(all(ord)));

  return ans;
}

pair<int, vector<ll> > search(int v, int p) {
  int np = 0;  // number of other elements
  vector<ll> dp(np + 1);  // dp[i] = (i elements) -> v -> (n - i) elements
  dp[0] = 1;

  rep (i, adj[v].size()) {
    if (adj[v][i].first == p) continue;
    pair<int, vector<ll> > tm = search(adj[v][i].first, v);
    int nq = tm.first;
    vector<ll> &dq = tm.second;

    if (adj[v][i].second == GT) {
      reverse(all(dp));
      reverse(all(dq));
    }

    int nr = np + nq + 1;
    vector<ll> dr(nr + 1);
    for (int ip = 0; ip <= np; ++ip) {
      for (int iq = 0; iq <= nq; ++iq) {
        for (int k = 0; k <= iq; ++k) {
          ll c1 = cmb[ip        + k           ][ip     ];
          ll c2 = cmb[(np - ip) + (nq - k + 1)][np - ip];
          ll c = ((c1 * c2) % MOD) * ((dp[ip] * dq[iq]) % MOD);
          (dr[ip + k] += c) %= MOD;
        }
      }
    }

    np = nr;
    dp.swap(dr);
    if (adj[v][i].second == GT) reverse(all(dp));

    // debug("%d %d\n", v, adj[v][i].first); rep (i, np + 1) debug(" %lld", dp[i]); debug("\n");
  }

  assert((int)dp.size() == np + 1);
  return mp(np, dp);
}

void solve() {
  debug("%d\n", N);

  pair<int, vector<ll> > res = search(0, -1);
  int np = res.first;
  vector<ll> dp = res.second;

  ll ans = 0;
  for (int i = 0; i <= np; ++i) (ans += dp[i]) %= MOD;
  printf("%lld\n", ans);

  if (N <= 6) {
    assert(ans == naive());
    debug("PASSED SYSTEM TEST!\n");
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
