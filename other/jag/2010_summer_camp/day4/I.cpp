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

const ll L = 10000000000LL;

const int MAX_V = 1010;
const ll INF = 1LL << 60;

struct e_t {
  int to;
  ll cap, cst;
  int rev;
};

int V, S, T;

vector<e_t> adj[MAX_V];
ll pot[MAX_V], dst[MAX_V];
int prvv[MAX_V], prve[MAX_V];

void add_edge(int i, int j, ll cap, ll cst) {
  adj[i].push_back((e_t){j, cap, cst, adj[j].size()});
  adj[j].push_back((e_t){i, 0, -cst, adj[i].size() - 1});
}

// (final-flow, final-cost, min-cost)
pair<pair<ll, ll>, ll> min_cost_flow(ll req = INF) {
  ll flow = 0, cost = 0;
  ll min_cost = 0;
  memset(pot, 0, sizeof(pot));

  bool up;
  do {
    up = false;
    rep (v, V) rep (i, adj[v].size()) {
      if (adj[v][i].cap == 0) continue;
      ll c = pot[v] + adj[v][i].cst;
      int w = adj[v][i].to;
      if (c < pot[w]) {
        pot[w] = c;
        up = true;
      }
    }
  } while (up);

  while (flow < req) {
    fill(dst, dst + V, INF);
    priority_queue<pair<ll, int> > que;
    que.push(make_pair(0, S));
    dst[S] = 0;
    while (!que.empty()) {
      ll d = -que.top().first;
      int v = que.top().second;
      que.pop();
      if (d > dst[v]) continue;

      rep (i, adj[v].size()) {
        e_t &e = adj[v][i];
        int w = e.to;
        ll td = dst[v] + e.cst + pot[v] - pot[w];
        if (e.cap && td < dst[w]) {
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
    min_cost = min(min_cost, cost);
  }

  return mp(mp(flow, cost), min_cost);
}



int N, M;
vector<pair<int, int> > fwd[110];
int mem[110];

int search(int v) {
  if (v == N - 1) return 0;
  if (mem[v] != -1) return mem[v];
  int r = 0;
  rep (i, fwd[v].size()) r = max(r, fwd[v][i].second + search(fwd[v][i].first));
  return mem[v] = r;
}

int main() {
  scanf("%d%d", &N, &M);

  const int F = 100000;

  ll ans = 0;
  int b[110] = {0};
  rep (i, M) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    fwd[x].pb(mp(y, c));

    // y -> x, -c
    add_edge(y, x, F, -c);
    ans += -c;
    ++b[y];
    --b[x];
  }
  memset(mem, -1, sizeof(mem));
  int P = search(0);

  V = N + 2;
  S = N;
  T = N + 1;
  add_edge(S, N - 1, F, P);
  add_edge(0, T, F, 0);
  rep (v, N) {
    if (b[v] < 0) add_edge(S, v, -b[v], -L);
    if (b[v] > 0) add_edge(v, T, +b[v], -L);
    ans += abs(b[v]) * ll(L);
  }

  int s = 0;
  rep (v, N) s += abs(b[v]);

  ll f = min_cost_flow().second;
  printf("%lld\n", ans + f);

  return 0;
}

