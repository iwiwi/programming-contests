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
const char *OUTPUT_FORMAT = "%s"; //"Case #%d:\n%s";

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

const int INF = 1000000000;
const int MAX_N = 260;
const int MAX_T = 12;


void init() {}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////


int N;
int cost[MAX_N];
vector<int> ter;

int adj[MAX_N][MAX_N];
int prv_adj[MAX_N][MAX_N];

int opt[1 << MAX_T][MAX_N];
pair<bool, int> prv_opt[1 << MAX_T][MAX_N];

vector<int> sol;

void restore_path(int v, int w) {
  if (v == w) return;
  int p = prv_adj[v][w];
  restore_path(v, p);
  sol.pb(p);
}

void restore(int b, int v) {
  if (__builtin_popcount(b) == 1) {
    int t = ter[__builtin_ctz(b)];
    restore_path(t, v);
  } else if (prv_opt[b][v].first) {
    int e = prv_opt[b][v].second;
    restore(e, v);
    restore(b - e, v);
  } else {
    int w = prv_opt[b][v].second;
    restore_path(w, v);
    restore(b, w);
  }
}

int minimum_steiner_tree() {
  int T = ter.size();
  if (T == 0) return 0;

  rep (i, N) adj[i][i] = 0;
  rep (i, N) rep (j, N) prv_adj[i][j] = i;

  rep (k, N) rep (i, N) rep (j, N) {
    int t = adj[i][k] + cost[k] + adj[k][j];
    if (t < adj[i][j]) {
      adj[i][j] = t;
      prv_adj[i][j] = prv_adj[k][j];
    }
  }

  rep (b, 1 << T) rep (v, N) opt[b][v] = b == 0 ? 0 : INF;
  rep (i, T) opt[1 << i][ter[i]] = 0;

  for (int b = 1; b < (1 << T); b++) {
    rep (p, N) {
      int e = b;
      do {
        int t = opt[e][p] + opt[b-e][p];
        if (t < opt[b][p]) {
          opt[b][p] = t;
          prv_opt[b][p] = mp(true, e);
        }
        e = (e - 1) & b;
      } while (e != b);
    }
    rep (v, N) rep (w, N) {
      int t = opt[b][w] + cost[w] + adj[w][v];
      if (t < opt[b][v]) {
        opt[b][v] = t;
        prv_opt[b][v] = mp(false, w);
      }
    }
  }

  sol.pb(ter[0]);
  restore((1 << T) - 1, ter[0]);
  return cost[ter[0]] + opt[(1 << T) - 1][ter[0]];
}

void input() {
  int M, T;
  scanf("%d%d%d", &N, &T, &M);
  rep (t, T) ter.pb(t);

  rep (i, N) rep (j, N) adj[i][j] = i == j ? 0 : INF;
  rep (i, M) {
    int a, b;
    scanf("%d%d", &a, &b);
    adj[a][b] = adj[b][a] = 0;
  }

  rep (i, N) {
    scanf("%d", &cost[i]);
    cost[i] = cost[i] * (N + 1) + 1;
  }
}


void solve() {
  int a = minimum_steiner_tree();
  printf("%d %d\n", a / (N + 1), a % (N + 1));
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
      printf(OUTPUT_FORMAT, s->out_buf);
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
          printf(OUTPUT_FORMAT, out[out_c].c_str());
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
      printf(OUTPUT_FORMAT, out[out_c].c_str());
      out_c++;
    }

#else
    fprintf(stderr, "error: compile with -fopenmp !!\n");
#endif
  }

  exit(EXIT_SUCCESS);
}
