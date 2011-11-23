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

vector<pair<int, int> > adj[50010];
int pot[50010];

int main() {
  int N, M = 0;
  scanf("%d", &N);
  rep (i, N) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    ++b;
    adj[a].pb(mp(b, (b - a) - c));
    M = max(M, b);
  }

  rep (i, M) {
    adj[i].pb(mp(i + 1, 1));
    adj[i + 1].pb(mp(i, 0));
  }

  rep (i, M + 1) pot[i] = INT_MAX;
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pque;
  pot[0] = 0;
  pque.push(mp(0, 0));

  while (!pque.empty()) {
    int v = pque.top().first;
    int p = pque.top().second;
    pque.pop();
    if (p > pot[v]) continue;

    rep (i, adj[v].size()) {
      int tv = adj[v][i].first;
      int tp = p + adj[v][i].second;
      if (tp < pot[tv]) {
        pot[tv] = tp;
        pque.push(mp(tv, tp));
      }
    }
  }
  printf("%d\n", -(pot[M] - M));

  return 0;
}

