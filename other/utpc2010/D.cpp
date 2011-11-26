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

map<string, vector<pair<string, int> > > adj;
map<string, int> mem;

void saiki(const string &s, int t) {
  if (mem.count(s)) {
    if (mem[s] != t) throw 0;
    return;
  }

  mem[s] = t;
  tr (adj[s], ite) saiki(ite->first, t + ite->second);
}


int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    adj.clear();
    
    rep (i, N) {
      char str1[256], str2[256];
      int k;
      scanf(" 1 %s = 10^%d %s", str1, &k, str2);
      adj[string(str1)].pb(mp(string(str2), k));
      adj[string(str2)].pb(mp(string(str1), -k));
    }

    mem.clear();
    try {
      tr (adj, ite) {
        const string &s = ite->first;
        if (mem.count(s)) continue;
        saiki(s, 0);
      }
      puts("Yes");
    } catch (...) {
      puts("No");
    }
  }
  
  return 0;
}

