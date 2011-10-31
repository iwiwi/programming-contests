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

int N, M, K;
vector<int> adj[1000010];

bool vis[1000010];

int main() {
  while (3 == scanf("%d%d%d", &N, &M, &K)) {
    rep (i, N) adj[i].clear();
    rep (i, M) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      adj[a].pb(b);
      adj[b].pb(a);
    }

    vector<int> degs;
    memset(vis, 0, sizeof(vis));
    rep (v, N) if (!vis[v]) {
      int cc = 0;
      queue<int> que;
      que.push(v);
      vis[v] = true;
      while (!que.empty()) {
        int w = que.front();
        que.pop();
        ++cc;
        rep (i, adj[w].size()) {
          int x = adj[w][i];
          if (vis[x]) continue;
          vis[x] = true;
          que.push(x);
        }
      }
      degs.pb(cc);
    }

    int L = degs.size();

    // if (K == 1) {
    //   printf("%d\n", (L + 1) / 2);
    //   continue;
    // }

    sort(all(degs));
    reverse(all(degs));
    rep (i, degs.size()) degs[i] = min(degs[i], K);

    int ones = 0, rest = 0;
    rep (i, L) {
      if (degs[i] > 1) {
        if (rest == 0) rest += degs[i];
        else rest = (rest - 1) + (degs[i] - 1);
      }
      else {
        ++ones;
      }
    }

    int ans = 0;
    for (;;) {
      if (rest == 0 && ones <= 2) break;
      if (ones <= rest) break;

      if (ones >= 2) {
        ones -= 2;
        ++ans;
        int tmp = min(K, 1 + 1);
        if (tmp == 1) {
          ++ones;
        } else {
          if (rest == 0) rest += tmp;
          else rest = (rest - 1) + (tmp - 1);
        }
      }
      else {
        ++ans;
        break;
      }
    }

    printf("%d\n", ans);

    // rep (i, degs.size()) printf("%d ", degs[i]); puts("");
  }

  return 0;
}

