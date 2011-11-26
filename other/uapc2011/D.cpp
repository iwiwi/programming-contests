#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back

typedef long long ll;

const int MAX_V = 510;

int V, wgh[MAX_V][MAX_V];

int minimum_cut() {
  int i, j, a, b, c, res = INT_MAX;
  vector<int> v, p(V);
  for (i = 0; i < V; i++) v.push_back(i);
  for (int n = V; n > 1; n--) {
    for (p[0] = i = 1; i < n; i++) p[i] = 0;
    for (i = 0; i < n; i++) {
      b = a;
      a = max_element(p.begin(), p.end()) - p.begin();
      c = p[a];
      p[a] = -1;
      for (j = 0; j < n; j++)
        if (p[j] >= 0) p[j] += wgh[v[a]][v[j]];
    }
    res = min(res, c);
    for (i = 0; i < n; i++) {
      wgh[v[i]][v[b]] += wgh[v[i]][v[a]];
      wgh[v[b]][v[i]] += wgh[v[a]][v[i]];
    }
    v.erase(v.begin() + a);
  }
  return res;
}

int main() {
  int N, M;
  while (scanf("%d%d", &N, &M) && (N | M)) {
    V = N;
    memset(wgh, 0, sizeof(wgh));

    int ans = 0;

    rep (i, M) {
      int x, y, c;
      scanf("%d%d%d", &x, &y, &c);
      if (c <= 0) ans += c;
      else wgh[x][y] = wgh[y][x] = c;
    }

    printf("%d\n", ans + minimum_cut());
  }
}
