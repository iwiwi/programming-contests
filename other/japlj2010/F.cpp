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

typedef long long ll;

int N, K, M;
vector<int> adj[100010];

bool done[100010];
ll mem0[100010][20];
ll mem1[100010][20];

void calc(int v, int p) {  
  ll dp0[20] = {0}, dp1[20] = {0}, dp2[20] = {0};
  dp0[0] = 1;
  
  rep (i, adj[v].size()) {
    int w = adj[v][i];
    if (w == p) continue;
    
    ll nxt0[20] = {0}, nxt1[20] = {0}, nxt2[20] = {0};

    rep (a, K + 1) {
      rep (b, a + 1) {
        nxt0[a] += (dp0[b] * mem0[w][a - b]) % M;
        
        nxt1[a] += (dp0[b] * mem1[w][a - b]) % M;
        nxt1[a] += (dp1[b] * mem0[w][a - b]) % M;
        
        nxt2[a] += (dp1[b] * mem1[w][a - b]) % M;
        nxt2[a] += (dp2[b] * mem0[w][a - b]) % M;
      }
    }

    rep (k, K + 1) {
      dp0[k] = nxt0[k] % M;
      dp1[k] = nxt1[k] % M;
      dp2[k] = nxt2[k] % M;
    }
  }

  rep (k, K + 1) {
    ll m0 = dp0[k];
    if (k > 0) m0 += dp2[k - 1] + dp1[k - 1];
    mem0[v][k] = m0 % M;

    mem1[v][k] = (dp0[k] + dp1[k]) % M;
    // printf("%d %d: %d %d\n", v + 1, k, mem0[v][k], mem1[v][k]);
  }
}

void saiki(int v, int p) {
  rep (i, adj[v].size()) {
    if (adj[v][i] != p) saiki(adj[v][i], v);
  }
  
  calc(v, p);
  done[v] = true;
}

void myassert(bool b) {
  if (!b) *(int*)0 = 0;
}

int main() {
  while (3 == scanf("%d%d%d", &N, &K, &M)) {
    myassert(2 <= N && N <= 100000);
    myassert(1 <= K && K <= 10);

    rep (i, N) adj[i].clear();
    rep (i, N - 1) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      
      adj[a].pb(b);
      adj[b].pb(a);

      myassert(0 <= a && a < N);
      myassert(0 <= b && b < N);
      myassert(a != b);
    }

    saiki(0, -1);
    printf("%lld\n", mem0[0][K] % M);

    rep (i, N) myassert(done[i]);
    return 0;
  }
  
  return 0;
}

