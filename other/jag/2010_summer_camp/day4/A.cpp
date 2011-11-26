#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

typedef long long ll;

const ll MOD = 1000000007;

int N, M, to[1010];
vector<int> rev[1010];

int cnt[1010];
bool start[1010], vis[1010];

ll saiki(int v) {
  vis[v] = true;
  if (start[v]) return 1;
  ll res = 1;
  rep (i, rev[v].size()) {
    int w = rev[v][i];
    res *= saiki(w);
    res %= MOD;
  }
  return (1 + res) % MOD;
}

int main() {
  scanf("%d%d", &N, &M);
  memset(to, -1, sizeof(to));
  rep (i, M) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a;
    --b;
    to[a] = b;
    rev[b].push_back(a);
  }

  ll res = 1;
  rep (i, N) if (!vis[i]) {
    vector<int> in;
    int x = i;
    for (;;) {
      vis[x] = true;
      ++cnt[x];
      
      // loop
      if (cnt[x] == 2) {
        start[x] = true;
        in.insert(in.end(), rev[x].begin(), rev[x].end());
      }
      else if (cnt[x] == 3) {
        break;
      }

      // root
      if (to[x] == -1) {
        start[x] = true;
        in.insert(in.end(), rev[x].begin(), rev[x].end());
        break;
      }
      else {
        x = to[x];
      }
    }
    
    sort(in.begin(), in.end());
    in.erase(unique(in.begin(), in.end()), in.end());
    ll t = 1;
    rep (j, in.size()) {
      int v = in[j];
      if (start[v]) continue;
      // printf(" %d: %d\n", v, saiki(v));
      t *= saiki(v);
      t %= MOD;
    }
    res *= (t + 1) % MOD;
    res %= MOD;
  }

  cout << res << endl;
  
  return 0;
}
