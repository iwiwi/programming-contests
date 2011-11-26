#include <cstdio>
#include <climits>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define mp make_pair

typedef long long ll;

int N;
ll X1[400010], Y1[400010], X2[400010], Y2[400010];

// vector<int> adj[160010];
int to[1600010];

void sweep(int a, ll *x1, ll *y1, ll *x2, ll *y2) {
  vector<pair<ll, pair<int, int> > > evts;
  rep (i, N) {
    evts.push_back(mp(x1[i], mp(2, i)));   // ’Ç‰Á
    evts.push_back(mp(x1[i], mp(0, i)));   // ¶‘¤‚Ìƒwƒ“
    evts.push_back(mp(x2[i], mp(1, i)));   // 
    evts.push_back(mp(x2[i], mp(-1, i)));  // íœ
  }
  sort(evts.begin(), evts.end());

  map<ll, int> ma;
  rep (k, evts.size()) {
    pair<int, int> e = evts[k].second;
    int t = e.first, i = e.second;
    if (t == -1) {
      ma.erase(y1[i]);
      ma.erase(y2[i]);
    }
    else if (t == 2) {
      // ma.insert(mp(y1[i], i * 4 + (a * 3 + 1) % 4));
      // ma.insert(mp(y2[i], i * 4 + (a * 3 + 3) % 4));
      ma.insert(mp(y1[i], i * 4 + (a + 1) % 4));
      ma.insert(mp(y2[i], i * 4 + (a + 3) % 4));
    }
    else if (t == 1) {
      ll y = y1[i];
      int v = i * 4 + a + 2;
      if (ma.size() == 0) continue;
      map<ll, int>::iterator ite = ma.upper_bound(y);
      if (ite == ma.begin()) continue;
      --ite;
      to[v] = ite->second;
    }
    else if (t == 0) {
      ll y = y2[i];
      int v = i * 4 + a + 0;
      map<ll, int>::iterator ite = ma.lower_bound(y);
      if (ite == ma.end()) continue;
      to[v] = ite->second;
    }
  }
}


int ans = 0;
int vis[1600010];
int pos[1600010];

int saiki(int v, int id) {
  for (int i = 0; ; i++) {
    if (vis[v] == id) {
      ans += i - pos[v];
      break;
    }
    else if (vis[v] != 0) break;

    vis[v] = id;
    if (to[v] == -1) break;
    v = to[v];
  }
}

int main() {
  scanf("%d", &N);
  rep (i, N) {
    scanf("%lld%lld%lld%lld", X1 + i, Y1 + i, X2 + i, Y2 + i);

    X1[i] = X1[i] * 3 + 1;
    Y1[i] = Y1[i] * 3 + 1;
    X2[i] = X2[i] * 3 - 1;
    Y2[i] = Y2[i] * 3 - 1;
  }
  
  memset(to, -1, sizeof(to));

  sweep(0, X1, Y1, X2, Y2);
  rep (i, N) {
    X1[i] *= -1;
    X2[i] *= -1;
  }
  sweep(1, Y1, X2, Y2, X1);

  rep (i, N * 4) {
    if (to[i] == -1) continue;
    //printf("%d %d -> %d %d\n", i / 4, i % 4, to[i] / 4, to[i] % 4);
    ///     printf("%d -> %d\n", i, to[i]);
  }

  rep (i, N * 4) {
    if (vis[i]) continue;
    saiki(i, i + 1);
  }
  if (ans % 4) {
    *(int*)0 = 0;
  }
  printf("%d\n", ans);

  return 0;
}
