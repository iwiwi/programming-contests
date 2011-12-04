// 2011/03/05 2:20
// 2011/03/05 2:27

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
#include <stdint.h>
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

const ll INF = ll(1) << 60;
const ll BIG = ll(1) << 40;  // |BIG * MAX_K| must fit in |long long|

const int MAX_V = 200010;  // |MAX_K * 2|

struct e_t {
  int to;
  ll cap, cst;
  int rev;
  ll org_cap;
};

int V, S, T;

vector<e_t> adj[MAX_V];
ll pot[MAX_V], dst[MAX_V];
int prvv[MAX_V], prve[MAX_V];

void add_edge(int i, int j, ll cap, ll cst) {
  adj[i].push_back((e_t){j, cap, cst, adj[j].size(), cap});
  adj[j].push_back((e_t){i, 0, -cst, adj[i].size() - 1, 0});
}

pair<ll, ll> min_cost_flow(int req = INT_MAX) {
  ll flow = 0, cost = 0;
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
      int v = que.top().second; que.pop();
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

    ll f = req - flow, c = 0;
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

int M, N, Ka, Kb;

int A[1000010], B[1000010];

int w(int a) { return __builtin_popcount(a); }

int main() {
  scanf("%d%d", &Ka, &M);

  rep (i, Ka) scanf("%d", A + i);

  int Kb = 0, tot = 0;
  rep (i, Ka) {
    // if (i > 0 && A[i - 1] == A[i]) continue;
    B[Kb++] = A[i];
    tot += w(A[i]);
  }
  // fprintf(stderr, "tot: %d\n", tot);

  V = Kb * 2;
  S = 0;
  T = Kb * 2 - 1;

  map<int, int> prv;
  rep (i, Kb) {
    if (i > 0) add_edge((i - 1) * 2 + 1, i * 2, M, 0);
    add_edge(i * 2, i * 2 + 1, 1, -BIG);
    add_edge(i * 2, i * 2 + 1, M, 0);

    int a = B[i];
    if (prv.count(a)) add_edge(prv[a] * 2 + 1, i * 2, 1, -w(a));
    prv[a] = i;
  }

  pair<ll, ll> res = min_cost_flow(M);

  // fprintf(stderr, "flow: %lld (req: %d)\n", res.first, M);
  // fprintf(stderr, "cost: %lld\n", res.second);


  vector<string> vs;
  int mem[100] = {};
  rep (i, Ka) {
    int a = A[i];
    int b = find(mem, mem + M, a) - mem;
    if (b == M) {
      for (b = 0; mem[b] != 0; ++b);
    }

    if (mem[b] != a) {
      stringstream ss;
      ss << char('a' + b) << "=" << a;
      vs.pb(ss.str());
      mem[b] = a;
    }
    vs.pb(string("print(") + char('a' + b) + ")");

    int v = i * 2 + 1;
    rep (j, adj[v].size()) {
      e_t &e = adj[v][j];
      if (e.cst == -w(a) && e.cap == 0) {
        goto reuse;
      }
    }
    mem[b] = 0;  // dispose
 reuse:;
  }

  cout << vs.size() << " " << (tot + res.second + BIG * Kb) << endl;
  rep (i, vs.size()) cout << vs[i] << endl;

  return 0;
}

