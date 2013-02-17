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

const ll INF = (1E18) * 1.1;
const int MAX_NODES = 110 * 110;
const int A = 26;

ll pow26[110];

int alphabet2id(int a) {
  return a - 'a';
}

struct node_t {
  node_t *parent, *fail, *next[A];
  // MODIFY HERE!
  bool is_terminal;
  ll dp[110];
};

ll mul(ll x, ll y, ll lim) {
  if (x > lim / y + 1) return lim;
  else return min(lim, x * y);
}

void init() {
  pow26[0] = 1;
  rep (i, 105) {
    pow26[i + 1] = mul(pow26[i], 26, INF);
  }
}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

node_t nodes[MAX_NODES], *root;
int num_nodes;

node_t *new_node() {
  node_t *p = &nodes[num_nodes++];
  p->parent = p->fail = NULL;
  rep (i, A) p->next[i] = NULL;
  // MODIFY HERE!
  p->is_terminal = 0;
  memset(p->dp, -1, sizeof(p->dp));
  return p;
}

void construct(const vector<string> &words) {
  num_nodes = 0;
  root = new_node();
  rep (i, words.size()) {
    const string &w = words[i];
    node_t *p = root;
    rep (j, w.length()) {
      node_t *&q = p->next[alphabet2id(w[j])];
      if (!q) q = new_node();
      q->parent = p;
      p = q;
    }
    // MODIFY HERE!
    p->is_terminal = 1;
  }

  queue<node_t*> que;
  que.push(root);
  while (!que.empty()) {
    node_t *p = que.front();
    que.pop();
    rep (i, A) {
      node_t *&q = p->next[i];
      if (!q) q = p->fail ? p->fail->next[i] : root;
      else {
        node_t *r = p->fail;
        while (r && !r->next[i]) r = r->fail;
        q->fail = r ? r->next[i] : root;
        que.push(q);
        // MODIFY HERE!
        q->is_terminal |= q->fail->is_terminal;
      }
    }
  }
}

int L, N;
ll K;
vector<string> name;

ll all;

void input() {
  cin >> L >> K >> N;
  name.resize(N);
  rep (i, N) cin >> name[i];
}

ll getit(int l, node_t *now, bool contained) {
  contained |= now->is_terminal;
  if (contained) return pow26[l];
  if (l == 0) return 0;
  if (now->dp[l] != -1) return now->dp[l];

  // if (contained) puts("CONTAINED!");

  ll res = 0;
  rep (a, 26) res = min(INF, res + getit(l - 1, now->next[a], contained));
  return now->dp[l] = res;
}

void solve() {
  construct(name);

  node_t *now = root;
  ll rank = K - 1;
  bool contained = false;
  string ans = "";
  rep (i, L) {
    rep (a, 26) {
      ll c = getit(L - i - 1, now->next[a], contained);
      // printf("%d %c: %lld\n", i, 'a' + a, c);
      if (rank < c) {
        ans += char('a' + a);
        now = now->next[a];
        contained |= now->is_terminal;
        goto next;
      } else {
        rank -= c;
      }
    }
    goto dmp;
 next:;
  }

  puts(ans.c_str());
  return;

dmp:;
  puts("unnamed baby :(");
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
