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




#include <fstream>
#include <iomanip>
#include <cstdarg>

typedef string v_label_t;
typedef int e_label_t;

void graphviz_undirected(int, vector<int>, v_label_t*, e_label_t*, const char*, ...);
__attribute__((format(printf, 5, 6)))

void graphviz_undirected(int V, vector<int> *adj,
                         v_label_t *v_label = NULL, vector<e_label_t> *e_label = NULL,
                         const char* filename = "viz", ...) {
  system("mkdir -p viz");
  ofstream ofs("viz/tmp.dot");
  assert(ofs);
  ofs << setprecision(1) << setiosflags(ios::fixed);

  ofs << "graph {" << endl;
  ofs << "  graph [size = \"40.0, 40.0\"];" << endl;

  rep (v, V) {
    ofs << "  " << v << " [";
    if (v_label) ofs << " label = \"" << v_label[v] << "\",";

    // 頂点番号を 1-indexed で表示したければ以下
    // ofs << " label = \"" << (v + 1) << "\",";

    // 頂点をただの点にしたければ以下
    // ofs << "label = \"\", fixedsize = true, width = 0.1, height = 0.1, ";

    ofs << "];" << endl;

    rep (i, adj[v].size()) {
      if (adj[v][i] >= v) {
        ofs << "  " << v << " -- " << adj[v][i];
        if (e_label) {
          e_label_t &e = e_label[v][i];
          ofs << " [label = \"" << e << "\"];";
        }
        ofs << endl;
      }
    }
  }

  ofs << "}" << endl;
  ofs.close();

  char bf[1024], bc[1024];
  va_list args;
  va_start(args, filename);
  vsnprintf(bf, sizeof(bf), filename, args);
  va_end(args);
  snprintf(bc, sizeof(bc), "dot -Kdot -Tpng -o viz/%s.png viz/tmp.dot", bf);
  system(bc);

  return;

  // 各アルゴリズムでの見栄えを試す
  static const char *algo[] = { "dot", "neato", "fdp", "twopi", "circo" };
  rep (i, sizeof(algo) / sizeof(algo[0])) {
    snprintf(bc, sizeof(bc), "dot -K%s -Tpng -o viz/%s.%s.png viz/tmp.dot", algo[i], algo[i], bf);
    system(bc);
  }
}




void init() {}



BEGIN_SOLVER ///////////////////////////////////////////////////////////////////////////////////////

int P, W;
vector<int> adj[410];
bool con[410][410];

void input() {
  scanf("%d%d", &P, &W);
  memset(con, 0, sizeof(con));
  rep (v, P) con[v][v] = true;
  rep (i, W) {
    int v, w;
    scanf("%d,%d", &v, &w);
    adj[v].pb(w);
    adj[w].pb(v);
    con[v][w] = con[w][v] = true;
  }
}

int D;
vector<int> vs[410];

void bfs() {
  int pot[410];
  queue<int> que;
  memset(pot, -1, sizeof(pot));

  pot[0] = 0;
  que.push(0);

  D = -1;
  while (!que.empty()) {
    int v = que.front();
    que.pop();

    vs[pot[v]].pb(v);
    if (v == 1) D = pot[v];

    rep (i, adj[v].size()) {
      int tv = adj[v][i];
      if (pot[tv] != -1) continue;
      pot[tv] = pot[v] + 1;
      que.push(tv);
    }
  }
}

map<int, map<int, int> > dp[410];

void solve() {
  bfs();

  dp[0][0][0] = adj[0].size();
  for (int d = 1; d < D; ++d) {
    rep (i, vs[d].size()) {
      int v = vs[d][i];

      tr (dp[d - 1], ite1) {
        int p1 = ite1->first;
        if (con[p1][v] == false) continue;

        int res = 0;
        tr (ite1->second, ite2) {
          int p2 = ite2->first;

          int tmp = ite2->second;
          rep (w, P) {
            if (con[v][w] && !con[p1][w] && !con[p2][w]) ++tmp;
          }
          res = max(res, tmp);
        }

        dp[d][v][p1] = res;
      }
    }
  }

  int ans = 0;
  {
    int d = D - 1;
    tr (dp[d], ite1) {
      int v = ite1->first;
      if (con[v][1] == false) continue;

      tr (ite1->second, ite2) {
        ans = max(ans, ite2->second);
      }
    }
  }

  printf("%d %d\n", D - 1, ans - (D - 1));
  // printf("%d %d (%d)\n", D - 1, ans - (D - 1), P);
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
