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

const int MAX_N = 2000;

void init() {}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

bool vis[MAX_N];
int ord[MAX_N], num, id[MAX_N];

void dfs1(int v) {
  if (vis[v]) return;
  vis[v] = true;
  rep (w, N) if (X < R[v][w]) dfs1(w);
  ord[num++] = v;
}

void dfs2(int v) {
  if (vis[v]) return;
  vis[v] = true; id[v] = num;
  rep (w, N) if (X < R[w][v]) dfs2(w);
}

void scc() {
  rep (i, N) vis[i] = 0;
  num = 0;
  for (int i = 0; i < N; i++) dfs1(i);
  rep (i, N) vis[i] = 0;
  num = 0;
  for (int i = N-1; i >= 0; i--) if (!vis[ord[i]]) dfs2(ord[i]), num++;
}



int N, K;
ll C, inX[2], A[2], B[2], M[2];

void input() {
  cin >> N >> K >> C;
  rep (i, 2) cin >> inX[i] >> A[i] >> B[i] >> M[i];
}

map<int, ll> F[2];
ll get_f(int a, int i) {
  if (F[a].count(i)) return F[a][i];
  else {
    if (i == 0) return F[a][0] = inX[a];
    else return F[a][i] = (A[a] * get_f(a, i - 1) + B[a]) % M[a];
  }
}

ll X, R[2010][2010];

ll naive() {
  vector<ll> xs(1, 0);
  rep (i, N) rep (j, N) xs.pb(R[i][j]);
  sort(all(xs));
  ll ans = 1LL << 60;

  rep (i, xs.size()) {
    X = xs[i];
    scc();

    vector<int> oks;
    vector<int> outdeg(num), size(num);
    rep (v, N) {
      rep (w, N) if (R[v][w] > X && id[v] != id[w]) ++outdeg[id[v]];
      ++size[id[v]];
    }
    rep (i, num) if (outdeg[i] == 0) oks.pb(size[i]);

    if ((int)oks.size() >= K) {
      sort(all(oks));
      ll cst = X;
      rep (i, K) cst += oks[i] * C;
      ans = min(ans, cst);
    }
  }

  return ans;
}

void solve() {
  X = 0;
  rep (i, N) {
    rep (j, N) {
      if (i > j) R[i][j] = get_f(0, i * (i - 1) / 2 + j);
      if (i < j) R[i][j] = get_f(1, j * (j - 1) / 2 + i);
      //printf("%5lld ", R[i][j]);
      X = max(X, R[i][j]);
    }
    //puts("");
  }

  ll ans = 1LL << 60;
  for (int trial = 0; X >= 0; ++trial) {
    scc();
    vector<int> oks;

    vector<int> outdeg(num), size(num);
    rep (v, N) {
      rep (w, N) if (R[v][w] > X && id[v] != id[w]) ++outdeg[id[v]];
      ++size[id[v]];
    }
    rep (i, num) if (outdeg[i] == 0) oks.pb(size[i]);

    ll least_x = 0;
    rep (v, N) rep (w, N) if (id[v] != id[w] && R[v][w] <= X) {
      if (outdeg[id[v]] == 0) least_x = max(least_x, R[v][w]);
      // else if (id[v] > id[w]) least_x = max(least_x, R[v][w]);
    }
    debug("[%5d] X = %lld -> %lld (oks: %d)\n", trial, X, least_x, (int)oks.size());
    X = least_x;

    if ((int)oks.size() >= K) {
      sort(all(oks));
      ll cst = X;
      rep (i, K) cst += oks[i] * C;
      ans = min(ans, cst);
    }

    --X;
  }

  // assert(ans == naive());
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
  const int L = 1;
  if (c - (nth - 1) / 2 <= 0) fprintf(stderr, "[ %.3f: case %d / %d ]\n", sec(), c, C);
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
