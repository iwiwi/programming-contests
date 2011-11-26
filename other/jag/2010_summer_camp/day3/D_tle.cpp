#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

int prv[80010], to[80010], crr[40010];
bool ava[80010];
map<pair<int, int>, int> edges;

int vis[40010], que[40010];

int main() {
  int N, K;
  scanf("%d%d", &N, &K);

  int id_n = 0, e = 0;
  memset(crr, -1, sizeof(crr));
  rep (k, K) {
    int q, u, v;
    scanf("%d%d%d", &q, &u, &v);
    if (u > v) swap(u, v);
    map<pair<int, int>, int>::iterator ite = edges.find(make_pair(u, v));
    
    int mye;
    if (ite == edges.end()) {
      edges.insert(make_pair(make_pair(u, v), e));
      mye = e;
      
      prv[e] = crr[u];
      to[e] = v;
      crr[u] = e++;

      prv[e] = crr[v];
      to[e] = u;
      crr[v] = e++;
    }
    else {
      mye = ite->second;
    }

    if (q == 1) ava[mye] = ava[mye + 1] = true;
    else if (q == 2) ava[mye] = ava[mye + 1] = false;
    else {
      int queh = 0, quet = 0;
      vis[u] = k;
      que[queh++] = u;
      while (quet < queh) {
        int x = que[quet++];
        if (x == v) goto ok;
        for (int e = crr[x]; e != -1; e = prv[e]) if (ava[e]) {
          int y = to[e];
          if (vis[y] != k) {
            vis[y] = k;
            que[queh++] = y;
          }
        }
      }
      puts("NO");
      continue;
    ok:
      puts("YES");
    }
  }

  return 0;
}
