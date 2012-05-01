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
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int N, A, B;
char fld[50][50];

int V, S, T;
int cap[100][100][2];
int cst[100][100][2];

int tcap[100][100][2];
int tcst[100][100][2];

bool vis[100];
int pot[100], dst[100], prvv[100], prve[100];

pair<int, int> min_cost_flow(int req) {
  memcpy(tcap, cap, sizeof(cap));
  memcpy(tcst, cst, sizeof(cst));

  int flow = 0, cost = 0;
  memset(pot, 0, sizeof(pot));

  while (flow < req) {
    fill(dst, dst + V, INT_MAX);
    memset(vis, 0, sizeof(vis));
    dst[S] = 0;

    for (;;) {
      int v = -1, d = INT_MAX;
      rep (tv, V) if (!vis[tv] && dst[tv] < d) {
        v = tv;
        d = dst[tv];
      }
      if (v == -1) break;
      vis[v] = true;

      rep (w, V) rep (e, 2) if (tcap[v][w][e]) {
        int td = dst[v] + tcst[v][w][e] + pot[v] - pot[w];
        assert(d <= td);
        if (td < dst[w]) {
          dst[w] = td;
          prvv[w] = v;
          prve[w] = e;
        }
      }
    }

    if (dst[T] == INT_MAX) break;
    rep (v, V) pot[v] += dst[v];

    int f = req - flow;
    for (int v = T; v != S; v = prvv[v]) {
      f = min(f, tcap[prvv[v]][v][prve[v]]);
    }

    for (int v = T; v != S; v = prvv[v]) {
      tcap[prvv[v]][v][prve[v]] -= f;
      tcap[v][prvv[v]][prve[v]] += f;
    }
    flow += f;
    cost += f * pot[T];
  }
  return mp(flow, cost);
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d%d", &N, &A, &B);
    if (N == 0 && A == 0 && B == 0) return 0;
    rep (i, N) scanf("%s", fld[i]);

    V = N * 2 + 2;
    S = N * 2;
    T = N * 2 + 1;
    memset(cap, 0, sizeof(cap));
    memset(cst, 0, sizeof(cst));

    int req = 0, crr = 0, c = 0;
    rep (i, N) rep (j, N) {
      switch (fld[i][j]) {
        case 'C':
          cap[S][i    ][0] += 1;
          cap[N + j][T][0] += 1;
          ++req;
          ++c;
          break;
        case '.':
          cap[N + j][i][0] += 1;
          break;
        case '/':
          break;
      }
    }

    rep (i, N) {
      cst[i][N + i][1] = -1;
      cst[N + i][i][1] = +1;
    }

    int prv_a = 0, ans = -1;
    for (int tot = 0; tot <= N * N; ++tot) {
      int a = tot * A / B;
      rep (i, N) {
        cap[S    ][N + i][1] += a - prv_a;
        cap[N + i][i    ][1] += a - prv_a;
        cap[i    ][T    ][1] += a - prv_a;
        req += a - prv_a;
        crr += a - prv_a;
      }
      prv_a = a;

      pair<int, int> tf = min_cost_flow(req);

      int tmp = crr - tf.second;

      if (tf.first == req && tmp >= tot) {
        ans = max(ans, tmp);
      }
    }

    printf("Case %d: ", ca);
    if (ans == -1) puts("impossible");
    else printf("%d\n", ans - c);
  }

  return 0;
}

