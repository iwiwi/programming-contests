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
int cnt[1000010];
int scr[1000010];

int main() {
  while (3 == scanf("%d%d%d", &N, &M, &K)) {
    memset(cnt, 0, sizeof(cnt));
    memset(scr, 0, sizeof(scr));

    set<pair<int, int> > es;

    rep (i, M) {
      char c;
      int a, b;
      scanf(" %c%d", &c, &a); --a;
      if (c == 't') {
        ++cnt[a];
      } else if (c == 'f') {
        scanf("%d", &b); --b;
        es.insert(mp(min(a, b), max(a, b)));
        scr[a] -= cnt[b];
        scr[b] -= cnt[a];
      } else if (c == 'u') {
        scanf("%d", &b); --b;
        es.erase(mp(min(a, b), max(a, b)));
        scr[a] += cnt[b];
        scr[b] += cnt[a];
      }
    }

    tr (es, ite) {
      int a = ite->first, b = ite->second;
      scr[a] += cnt[b];
      scr[b] += cnt[a];
    }

    rep (i, N) scr[i] += cnt[i];
    sort(scr, scr + N, greater<int>());
    printf("%d\n", scr[K - 1]);
  }

  return 0;
}

