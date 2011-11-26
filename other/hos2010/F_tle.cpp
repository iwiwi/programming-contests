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
#include <numeric>
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

const int MAX_V = 6010;
const double EPS = 1E-10;
const double INF = 1E30;

struct e_t {
  int to;
  ll cap;
  double cst;
  int rev;
};

int V, S, T;

vector<e_t> adj[MAX_V];
double pot[MAX_V], dst[MAX_V];
int prvv[MAX_V], prve[MAX_V];
bool vis[MAX_V];

void add_edge(int i, int j, ll cap, double cst) {
  // printf("%d-%d %lld %f\n", i, j, cap, cst);
  adj[i].push_back((e_t){j, cap, cst, adj[j].size()});
  adj[j].push_back((e_t){i, 0, -cst, adj[i].size() - 1});
}

pair<ll, double> min_cost_flow(ll req = INT_MAX) {
  ll flow = 0;
  double cost = 0;
  memset(pot, 0, sizeof(pot));

  bool up;
  rep (i, V) {
    up = false;
    rep (v, V) rep (i, adj[v].size()) {
      if (adj[v][i].cap == 0) continue;
      double c = pot[v] + adj[v][i].cst;
      int w = adj[v][i].to;
      if (c < pot[w] - EPS) {
        pot[w] = c;
        up = true;
      }
    }
    if (!up) break;
  }

  while (flow < req) {
    // puts("piyo");
    fill(dst, dst + V, INF);
    fill(vis, vis + V, false);
    priority_queue<pair<double, int> > que;
    que.push(make_pair(0.0, S));
    dst[S] = 0;
    while (!que.empty()) {
      int v = que.top().second; que.pop();
      if (vis[v]) continue;
      vis[v] = true;
      rep (i, adj[v].size()) {
        e_t &e = adj[v][i];
        int w = e.to;
        double td = dst[v] + e.cst + pot[v] - pot[w];
        if (!vis[w] && e.cap && td < dst[w] - EPS) {
          que.push(make_pair(-td, w));
          dst[w] = td;
          prvv[w] = v;
          prve[w] = i;
        }
      }
    }
    if (dst[T] == INF) break;
    rep (v, V) pot[v] += dst[v];

    ll f = req - flow;
    double c = 0;
    for (int v = T; v != S; v = prvv[v]) {
      f = min(f, adj[prvv[v]][prve[v]].cap);
      c += adj[prvv[v]][prve[v]].cst;
    }
    flow += f;
    cost += f * c;
    for (int v = T; v != S; v = prvv[v]) {
      e_t &e = adj[prvv[v]][prve[v]];
      e.cap -= f;
      adj[e.to][e.rev].cap += f;
    }
  }

  return make_pair(flow, cost);
}


typedef long long ll;

double sqr(double x) {
  return x * x;
}

ll req_flow;

void add_req_edge(int v, int w, ll req) {
  add_edge(v, T, req, 0);
  add_edge(S, w, req, 0);
  req_flow += req;
  //printf("add: %lld (%lld)\n", req, req_flow);
}

int main() {
  for (;;) {
    int M, N, K;
    scanf("%d%d%d", &M, &N, &K);
    if (M == 0 && N == 0 && K == 0) return 0;

    int A[50][50];
    rep (i, M) rep (j, N) scanf("%d", &A[i][j]);


    ll row[50], col[50];
    rep (i, M) {
      row[i] = 0;
      rep (j, N) row[i] += A[i][j];
    }
    rep (j, N) {
      col[j] = 0;
      rep (i, M) col[j] += A[i][j];
    }
    ll sum = accumulate(row, row + M, 0);

    V = M + N + 4;
    int myS = M + N;
    int myT = M + N + 1;
    S = M + N + 2;
    T = M + N + 3;
    rep (i, V) adj[i].clear();
    req_flow = K;

    add_req_edge(S, myS, K);
    add_req_edge(myT, T, K);

    double ans = 0;
    rep (i, M) {
      int v = i;
      double x = row[i] * (double)K / (double)sum;
      ll xfl = row[i] * (ll)K / sum;
      ll xce = (row[i] * (ll)K + sum - 1) / sum;
      double cfl = sqr(x - xfl);
      double cce = sqr(x - xce);

      ans += cfl;
      add_req_edge(myS, v, xfl);
      if (row[i] * (ll)K % sum != 0) add_edge(myS, v, 1, cce - cfl);
    }
    rep (j, N) {
      int v = M + j;
      double x = col[j] * (double)K / (double)sum;
      ll xfl = col[j] * (ll)K / sum;
      ll xce = (col[j] * (ll)K + sum - 1) / sum;
      double cfl = sqr(x - xfl);
      double cce = sqr(x - xce);

      // printf("col %d: %lld (%lld %lld %lld)\n", j, xfl, (ll)col[j], (ll)K, sum);

      ans += cfl;
      add_req_edge(v, myT, xfl);
      if (col[j] * (ll)K % sum != 0) add_edge(v, myT, 1, cce - cfl);
    }
    rep (i, M) rep (j, N) {
      int v1 = i;
      int v2 = M + j;
      // puts("ahoge");
      // add_edge(i, v1, K, 0);
      // add_edge(v2, M + j, K, 0);

      double x = A[i][j] * (double)K / (double)sum;
      ll xfl = A[i][j] * (ll)K / sum;
      ll xce = (A[i][j] * (ll)K + sum - 1) / sum;
      double cfl = sqr(x - xfl);
      double cce = sqr(x - xce);

      ans += cfl;
      add_req_edge(v1, v2, xfl);
      if (A[i][j] * (ll)K % sum != 0) add_edge(v1, v2, 1, cce - cfl);
    }

    pair<ll, double> res = min_cost_flow(req_flow);
    // !printf("%lld %lld %f\n", req_flow, res.first, res.second);

    rep (i, M) {
      rep (j, N) {
        // int v1 = M + N + 2 * (N * i + j);
        // int v2 = M + N + 2 * (N * i + j) + 1;
        int v1 = i;
        int v2 = M + j;
        ll t = (A[i][j] * (ll)K + sum - 1) / sum;

        rep (k, adj[v1].size()) {
          e_t &e = adj[v1][k];
          if (e.to == v2) {
            t -= e.cap;
            // printf("%d: %lld\n", e.to, e.cap);
          }
        }
        if (j > 0) cout << " ";
        cout << t;
      }
      cout << endl;
    }
    cout << endl;
  }

  return 0;
}

