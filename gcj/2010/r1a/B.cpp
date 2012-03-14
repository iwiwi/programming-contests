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

const int MAX_OUT = 1000;
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


const int INF = 987654321;
const int K = 256;

BEGIN_SOLVER ///////////////////////////////////////////////////////////////////

int D, I, M, N;
int A[110];

void input() {
  scanf("%d%d%d%d", &D, &I, &M, &N);
  rep (i, N) scanf("%d", A + i);
}


int dp[110][300];

void solve() {
  // fill(dp[0], dp[0] + K, INF);
  // dp[0][A[0]] = 0;
  memset(dp, 0, sizeof(dp));
  
  for (int i = 1; i <= N; i++) {
    int a = A[i - 1];
    
    rep (x, K) {
      int t = dp[i - 1][x] + D;
      rep (y, K) {
        if (abs(x - y) <= M) t = min(t, dp[i - 1][y] + abs(x - a));
      }
      dp[i][x] = t;
    }

    rep (x, K) {
      rep (y, K) {
        int d = abs(x - y);
        if (M == 0) continue;
        dp[i][y] = min(dp[i][y], dp[i][x] + I * (d / M + (d % M ? 1 : 0)));
      }
    }
    // rep (x, 20) debug("%d ", dp[i][x]); debug("\n");
  }

  printf("%d\n", *min_element(dp[N], dp[N] + K));
}










////////////////////////////////////////////////////////////////////////////////
// Template
////////////////////////////////////////////////////////////////////////////////
  
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
}


END_SOLVER /////////////////////////////////////////////////////////////////////


double sec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}



void print_status(int c, int C, double t0, double t1, int nth) {
  static const int L = 20;
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
    if (strcmp(argv[i], "-p") == 0) parallel = true;
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
  
  int C;
  scanf("%d", &C);
  
  if (!parallel) {
    if (status) fprintf(stderr, "[ mode: single thread ]\n");
    
    rep (c, C) {
      if (status) print_status(c, C, t0, t1, 1);
      
      solver *s = new solver();
      assert(s != NULL);
      s->input();
      s->solve();
      printf(OUTPUT_FORMAT, c + 1, s->out_buf);
      delete s;
    }
  }
  else {
#ifdef _OPENMP

    int nth = omp_get_max_threads();
    if (status) fprintf(stderr, "[ mode: parallel (%d) ]\n", nth);

    vector<string> out(C);
    int done = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);
    
#pragma omp parallel for schedule(dynamic, 1)
    rep (c, C) {
      solver *s = new solver();
      assert(s != NULL);

      omp_set_lock(&lock);
      if (status) print_status(done, C, t0, t1, nth);
      int myid = done++;
      s->input();
      omp_unset_lock(&lock);

      s->solve();

      out[myid] = s->out_buf;
      delete s;
    }

    omp_destroy_lock(&lock);

    rep (c, C) {
      printf(OUTPUT_FORMAT, c + 1, out[c].c_str());
    }
    
#else
    fprintf(stderr, "error: compile with -fopenmp !!\n");
#endif
  }

  exit(EXIT_SUCCESS);
}
