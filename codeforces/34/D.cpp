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

vector<int> adj[1000010];

int par[1000010];

void saiki(int v, int p) {
  par[v] = p;
  rep (i, adj[v].size()) {
    if (adj[v][i] == p) continue;
    saiki(adj[v][i], v);
  }
}

int main() {
  int N, R1, R2;
  while (3 == scanf("%d%d%d", &N, &R1, &R2)) {
    --R1;
    --R2;
    
    rep (i, N) adj[i].clear();
    rep (i, N) if (i != R1) {
      int p;
      scanf("%d", &p);
      --p;
      adj[i].pb(p);
      adj[p].pb(i);
    }

    saiki(R2, -1);
    bool first = true;
    rep (i, N) if (i != R2) {
      if (first) first = false;
      else putchar(' ');
      printf("%d", par[i] + 1);
    }
    puts("");
  }
  
  return 0;
}

