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

const int MAX_N = 1000000;

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




int N;


int main() {
  while (1 == scanf("%d", &N)) {
    init(N);
    
    vector<pair<int, int> > cls;
    rep (i, N - 1) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a; --b;

      if (find(a, b)) cls.pb(mp(a, b));
      else unite(a, b);
    }

    vector<pair<int, int> > bui;
    rep (i, N) rep (j, i) {
      if (!find(j, i)) {
        bui.pb(mp(j, i));
        unite(j, i);
      }
    }

#define F first
#define S second
    
    printf("%d\n", (int)cls.size());
    rep (i, cls.size()) {
      printf("%d %d %d %d\n", cls[i].F + 1, cls[i].S + 1, bui[i].F + 1, bui[i].S + 1);
    }
  }
  
  return 0;
}
