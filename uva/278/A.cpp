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
vector<pair<set<int>, ll>*> sets;

int main() {
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    sets.clear();
    sets.resize(N);
    rep (i, N) {
      sets[i] = new pair<set<int>, ll>();
      sets[i]->first.insert(i);
      sets[i]->second = i;
    }

    rep (i, M) {
      int t, p;
      scanf("%d%d", &t, &p);
      --p;
      if (t == 3) {
        int sz = sets[p]->first.size();
        printf("%d %lld\n", sz, sets[p]->second + sz);
        // tr (*sets[p], ite) printf(" %d", *ite + 1); puts("");
      } else {
        int q;
        scanf("%d", &q);
        --q;
        if (t == 1) {
          pair<set<int>, ll> *a = sets[p], *b = sets[q];
          if (a == b) continue;
          if (a->first.size() < b->first.size()) swap(a, b);
          tr (b->first, ite) {
            a->first.insert(*ite);
            a->second += *ite;
            sets[*ite] = a;
          }
        } else {
          sets[p]->first.erase(p);
          sets[p]->second -= p;

          sets[q]->first.insert(p);
          sets[q]->second += p;

          sets[p] = sets[q];
        }
      }
    }
  }

  return 0;
}

