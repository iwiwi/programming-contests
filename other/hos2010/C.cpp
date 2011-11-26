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
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

const int MAX_N = 100000;

int par[MAX_N], rank[MAX_N];

void init(int n) {
  for (int i = 0; i < n; i++) {
    par[i] = i;
    rank[i] = 0;
  }
}

int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}

void unite(int x, int y) {
  x = root(x);
  y = root(y);
  if (x == y) return;

  if (rank[x] < rank[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rank[x] == rank[y]) rank[x]++;
  }
}

bool find(int x, int y) {
  return root(x) == root(y);
}

#include <climits>

int N, M;
int sid[110];

int main() {
  for (;;) {
    scanf("%d%d", &N, &M);
    if (N == 0 && M == 0) return 0;

    int t = 0;
    rep (i, N) {
      int s;
      scanf("%d", &s);
      if (s == 1) sid[i] = t++;
      else sid[i] = -1;
    }

    vector<pair<int, pair<int, int> > > edg(M);
    rep (i, M) {
      scanf("%d%d%d", &edg[i].second.first, &edg[i].second.second, &edg[i].first);
      --edg[i].second.first;
      --edg[i].second.second;
    }
    sort(all(edg));

    int ans = INT_MAX;
    rep (b, 1 << t) {
      init(N);
      int tmp = 0, num = 0;

      rep (i, M) {
        int v = edg[i].second.first;
        int w = edg[i].second.second;

        if (sid[v] != -1 && (b & (1 << sid[v]))) continue;
        if (sid[w] != -1 && (b & (1 << sid[w]))) continue;
        if (find(v, w)) continue;

        unite(v, w);
        tmp += edg[i].first;
        ++num;
      }
      if (num == N - __builtin_popcount(b) - 1) {
        ans = min(ans, tmp);
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}

