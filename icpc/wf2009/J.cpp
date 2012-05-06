#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <cassert>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef vector<int> vi;

const int INF = 1LL << 29;

int N, E;
vector<pair<int, int> > adj[110];

void normalize(vi &a) {
  assert((int)a.size() == E * 2 + 1);
  int t = INF;
  for (int ax = E; ax >= -E; --ax) {
    t = a[E + ax] = min(a[E + ax], t);
  }
}

vi doit(int s, vi a) {
  vi res(2 * E + 1, INF);
  s %= 60;
  for (int i = 0; i <= 1; ++i) {
    int d = s - i * 60;
    for (int x = -E; x <= E; ++x) {
      int tx = x + d;
      if (tx < -E || E < tx || a[E + x] + d > E) continue;
      res[E + tx] = min(res[E + tx], a[E + x] + d);
    }
  }
  normalize(res);
  return res;
}

vi mergeit(vi a, vi b) {
  vi res(2 * E + 1, INF);
  rep (iter, 2) {
    for (int ax = -E; ax <= E; ++ax) {
      int bx = max(ax, -E - ax);
      if (bx < -E || E < bx || ax + bx < -E) continue;
          int ay = a[E + ax];
          int by = b[E + bx];
          if (ay + by > E) continue;
          res[E + min(ax, bx)] = min(res[E + min(ax, bx)], max(ay, by));
    }
    a.swap(b);
  }
  normalize(res);
  return res;
}

vi search(int v, int p) {
  vector<int> res(2 * E + 1, INF);
  for (int x = -E; x <= 0; ++x) res[E + x] = 0;

  rep (i, adj[v].size()) if (adj[v][i].first != p) {
    vi tmp = search(adj[v][i].first, v);
    tmp = doit(adj[v][i].second, tmp);
    res = mergeit(tmp, res);
  }

  return res;
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d", &N);
    if (N == 0) return 0;

    rep (i, N) adj[i].clear();
    rep (i, N - 1) {
      int a, b, s;
      scanf("%d%d%d", &a, &b, &s);
      --a;
      --b;
      adj[a].pb(mp(b, s));
      adj[b].pb(mp(a, s));
    }

    // lb: impossible, ub: possible
    int lb = -1, ub = 60 * 100 + 10;
    while (ub - lb > 1) {
      E = (lb + ub) / 2;
      vector<int> res = search(0, -1);

      if (*min_element(res.begin(), res.end()) != INF) {
        ub = E;
      } else {
        lb = E;
      }
    }
    printf("Case %d: %d\n", ca, ub);
  }
}
