#include <cstdio>
#include <queue>
#include <string>
#include <iostream>
#include <cctype>
#include <cassert>
#include <map>
#include <sstream>
#include <set>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)

typedef long long ll;

int N, M;

set<int> know[100010];
vector<int> memb[100010];
int par[300010];

int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}

int main() {
  scanf("%d%d", &N, &M);
  rep (i, M) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a; --b;
    know[a].insert(b);
  }

  rep (i, N) {
    memb[i].push_back(i);
    par[i] = i;
  }

  int Q;
  scanf("%d", &Q);
  rep (q, Q) {
    int t, a, b;
    scanf("%d%d%d", &t, &a, &b);
    --a;
    --b;
    a = root(a);
    b = root(b);

    if (t == 1) {
      //printf("%d: ", a + 1); tr (know[a], ite) printf("%d ", *ite + 1); puts("");
      //printf("%d: ", b + 1); tr (memb[b], ite) printf("%d ", *ite + 1); puts("");

      // query
      iter(know[a]) itea = know[a].begin();
      iter(memb[b]) iteb = memb[b].begin();
      while (itea != know[a].end() && iteb != memb[b].end()) {
        if (*itea == *iteb) goto ok;
        else if (*itea < *iteb) ++itea;
        else ++iteb;
      }

      puts("NO");
      continue;
    ok:
      puts("YES");
    }
    else {
      // merge
      if (memb[a].size() < memb[b].size()) swap(a, b);

      {
        int k = memb[a].size();
        memb[a].resize(memb[a].size() + memb[b].size());
        rep (i, memb[b].size()) memb[a][k + i] = memb[b][i];
        memb[b].clear();
      }
      tr (know[b], ite) know[a].insert(*ite);
      par[b] = a;
      know[b].clear();

      // !?
      par[N++] = a;
    }
  }

  return 0;
}
