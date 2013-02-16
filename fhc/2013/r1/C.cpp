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

int W, H, P, Q, N;
ll X, Y, A, B, C, D;

int xs[1000010], ys[1000010];

void input() {
  cin >> W >> H >> P >> Q >> N >> X >> Y >> A >> B >> C >> D;
}

int naive() {
  set<pair<int, int> > px;
  rep (i, N) px.insert(mp(xs[i], ys[i]));

  int ans = 0;
  rep (x, W) rep (y, H) {
    rep (dx, P) rep (dy, Q) {
      int tx = x + dx, ty = y + dy;
      // if (W <= tx || H <= ty) goto ng;
      if (px.count(mp(tx, ty))) goto ng;
    }
    ++ans;
 ng:;
  }
  return ans;
}

int segt_nz[1000010], segt_dif[1000010];

int segt_add(int a, int b, int v, int k, int l, int r) {
  if (r <= a || b <= l) return segt_dif[k] ? (r - l) : segt_nz[k];
  if (a <= l && r <= b) {
    segt_dif[k] += v;
    return segt_dif[k] ? (r - l) : segt_nz[k];
  }
  else {
    segt_nz[k] =
        segt_add(a, b, v, k * 2 + 1, l, (l + r) / 2) +
        segt_add(a, b, v, k * 2 + 2, (l + r) / 2, r);
    // debug("[%d, %d): %d, %d\n", l, r, segt_nz[k], segt_dif[k]);
    return segt_dif[k] ? (r - l) : segt_nz[k];
  }
}


void solve() {
  xs[0] = X;
  ys[0] = Y;
  for (int i = 1; i < N; ++i) {
    xs[i] = (xs[i - 1] * A + ys[i - 1] * B + 1) % W;
    ys[i] = (xs[i - 1] * C + ys[i - 1] * D + 1) % H;
  }

  W = W - P + 1;
  H = H - Q + 1;

  vector<pair<int, pair<int, int> > > evt;
  rep (i, N) {
    // debug(" %d %d\n", xs[i], ys[i]);
    evt.pb(mp(xs[i] - P + 1, mp(ys[i], +1)));
    evt.pb(mp(xs[i]     + 1, mp(ys[i], -1)));
  }
  sort(all(evt));

  memset(segt_nz, 0, sizeof(segt_nz));
  memset(segt_dif, 0, sizeof(segt_dif));
  ll ans = 0;
  int evt_i = 0, nz = 0;
  rep (x, W) {
    while (evt_i < (int)evt.size() && evt[evt_i].first <= x) {
      int y = evt[evt_i].second.first;
      int ylb = max(y - Q + 1, 0);
      int yub = min(y     + 1, H);
      // debug("[%d, %d) += %d\n", ylb, yub, evt[evt_i].second.second);
      nz = segt_add(ylb, yub, evt[evt_i].second.second, 0, 0, H);
      ++evt_i;
    }
    // debug("%d: %d - %d = %d\n", x, H, nz, H - nz);
    ans += H - nz;
  }

  if (0) {
    int ans_naive = naive();
    debug("%d vs %lld\n", ans_naive, ans);
    assert(ans_naive == ans);
  }

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
