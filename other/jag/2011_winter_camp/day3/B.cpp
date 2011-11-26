#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define mp make_pair
#define pb push_back

typedef long long ll;

int V, E;
vector<int> adj[100010];
int col[100010];
int cnt[2];

// Count vertices with color 0
void saiki(int v, int c) {
  if (col[v] != -1) {
    if (col[v] != c) throw 0;
    return;
  }
  col[v] = c;
  ++cnt[c];
  rep (i, adj[v].size()) saiki(adj[v][i], 1 - c);
}

bool dp[100010];

int main() {
  scanf("%d%d", &V, &E);
  rep (i, E) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a;
    --b;
    adj[a].pb(b);
    adj[b].pb(a);
  }

  memset(col, -1, sizeof(col));
  map<int, int> reds;
  int base = 0;
  try {
    rep (v, V) {
      if (col[v] != -1) continue;
      cnt[0] = cnt[1] = 0;
      saiki(v, 0);
      // printf("cnt: %d %d\n", cnt[0], cnt[1]);
      base += min(cnt[0], cnt[1]);
      ++reds[max(cnt[0], cnt[1]) - min(cnt[0], cnt[1])];
      // printf(" %d\n", max(cnt[0], cnt[1]) - min(cnt[0], cnt[1]));
    }
  } catch (...) {
    puts("-1");
    return 0;
  }

  // 0-1-2 Like DP
  vector<int> coins;
  tr (reds, ite) {
    int t = ite->first;
    if (t == 0) continue;
    int c = ite->second;
    for (int k = 1; k < c; k *= 2) {
      coins.pb(t * k);
      c -= k;
    }
    if (c > 0) coins.pb(t * c);
  }

  // printf("base = %d\n", base);
  dp[base] = true;
  rep (i, coins.size()) {
    int c = coins[i];
    // printf(" %d\n", c);
    for (int x = V; x >= c; --x) dp[x] |= dp[x - c];
  }

  int r = -1;
  for (int lo = V / 2, hi = (V + 1) / 2;;
       --lo, ++hi) {
    if (lo >= 0 && dp[lo]) {
      r = lo;
      break;
    }
    if (hi <= V && dp[hi]) {
      r = hi;
      break;
    }
  }
  // printf("r=%d\n", r);

  // Assertion
  if (r == -1) for (;;) puts("HELL WORLD!!");

  ll total = r * ll(V - r);
  cout << (total - E) << endl;
  return 0;
}
