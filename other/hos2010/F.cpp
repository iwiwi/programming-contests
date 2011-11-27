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
bool usd[MAX_V];

void add_edge(int i, int j, ll cap, double cst) {
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
    fill(dst, dst + V, INF);
    memset(usd, 0, sizeof(usd));
    priority_queue<pair<double, int> > que;
    que.push(make_pair(0.0, S));
    dst[S] = 0;
    while (!que.empty()) {
      int v = que.top().second; que.pop();
      if (usd[v]) continue;
      usd[v] = true;

      rep (i, adj[v].size()) {
        e_t &e = adj[v][i];
        int w = e.to;
        double td = dst[v] + e.cst + pot[v] - pot[w];
        if (!usd[w] && e.cap && td < dst[w]) {
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
    for (int v = T; v != S; v = prvv[v]) {
      f = min(f, adj[prvv[v]][prve[v]].cap);
    }
    for (int v = T; v != S; v = prvv[v]) {
      e_t &e = adj[prvv[v]][prve[v]];
      e.cap -= f;
      adj[e.to][e.rev].cap += f;
    }

    flow += f;
    cost += f * pot[T];
  }

  return make_pair(flow, cost);
}


typedef long long ll;

double sqr(double x) {
  return x * x;
}

double MARGIN = 1E6;

ll req_flow;
double pre_cost;

void add_req_edge(int v, int w, ll req) {
  add_edge(v, T, req, -MARGIN);
  add_edge(S, w, req, -MARGIN);
  req_flow += req;
  pre_cost += req * MARGIN * 2;
  //printf("add: %lld (%lld)\n", req, req_flow);
}

int main() {
  for (;;) {
    int H, W, K;
    scanf("%d%d%d", &H, &W, &K);
    if (H == 0 && W == 0 && K == 0) return 0;

    int A[50][50];
    rep (i, H) rep (j, W) scanf("%d", &A[i][j]);

    ll B[50][50];

    ll row[50], col[50];
    rep (i, H) {
      row[i] = 0;
      rep (j, W) row[i] += A[i][j];
    }
    rep (j, W) {
      col[j] = 0;
      rep (i, H) col[j] += A[i][j];
    }
    ll sum = accumulate(row, row + H, 0);

    V = H + W + 2;
    S = H + W;
    T = H + W + 1;
    rep (i, V) adj[i].clear();
    pre_cost = 0;
    req_flow = K;

    double ans = 0;
    rep (i, H) {
      double x = row[i] * (double)K / (double)sum;
      ll xfl = row[i] * (ll)K / sum;
      ll xce = (row[i] * (ll)K + sum - 1) / sum;
      double cfl = sqr(x - xfl);
      double cce = sqr(x - xce);

      ans += cfl;
      int v = i;
      add_req_edge(S, v, xfl);
      if (row[i] * (ll)K % sum != 0) add_edge(S, v, 1, cce - cfl);
    }
    rep (j, W) {
      int v = H + j;
      double x = col[j] * (double)K / (double)sum;
      ll xfl = col[j] * (ll)K / sum;
      ll xce = (col[j] * (ll)K + sum - 1) / sum;
      double cfl = sqr(x - xfl);
      double cce = sqr(x - xce);

      ans += cfl;
      add_req_edge(v, T, xfl);
      if (col[j] * (ll)K % sum != 0) add_edge(v, T, 1, cce - cfl);
    }
    rep (i, H) rep (j, W) {
      int v1 = i;
      int v2 = H + j;
      // add_edge(i, v1, K, 0);
      // add_edge(v2, H + j, K, 0);

      double x = A[i][j] * (double)K / (double)sum;
      ll xfl = A[i][j] * (ll)K / sum;
      ll xce = (A[i][j] * (ll)K + sum - 1) / sum;
      double cfl = sqr(x - xfl);
      double cce = sqr(x - xce);

      ans += cfl;
      add_req_edge(v1, v2, xfl);
      if (A[i][j] * (ll)K % sum != 0) add_edge(v1, v2, 1, cce - cfl);

      B[i][j] = xfl;
    }

    pair<ll, double> res = min_cost_flow(req_flow);
    // printf("HOGE: %lld %lld %f\n", req_flow, res.first, res.second);

    rep (y, H) {
      int v1 = y;
      rep (i, adj[v1].size()) {
        e_t &e = adj[v1][i];
        int v2 = e.to;
        if (H <= v2 && v2 < H + W) {
          int x = v2 - H;
          if (e.cap == 0) ++B[y][x];
        }
      }
    }

    rep (y, H) rep (x, W) cout << B[y][x] << (x + 1 == W ? '\n' : ' ');
    cout << endl;
  }

  return 0;
}

