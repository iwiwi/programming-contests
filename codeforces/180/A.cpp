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

int N, M;
int K[210];
pair<int, int> disk[210];


int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    rep (i, N) disk[i] = mp(-1, -1);

    rep (i, M) {
      scanf("%d", K + i);
      rep (j, K[i]) {
        int a;
        scanf("%d", &a);
        --a;
        disk[a] = mp(i, j);
      }
    }

    vector<pair<int, int> > ans;

    int to = -1;
    rep (i, M) rep (j, K[i]) {
      ++to;

      int fr = -1, tm = -1;
      rep (p, N) {
        if (disk[p] == mp(i, j)) fr = p;
        if (disk[p].first == -1) tm = p;
      }
      //printf("%d -> %d\n", fr, to);

      if (fr == to) continue;
      if (disk[to].first == -1) {
        ans.pb(mp(fr, to)); swap(disk[fr], disk[to]);
      } else {
        ans.pb(mp(to, tm)); swap(disk[to], disk[tm]);
        ans.pb(mp(fr, to)); swap(disk[fr], disk[to]);
      }
    }

    // rep (p, N) printf("%d-%d ", disk[p].first, disk[p].second); puts("");

    printf("%d\n", (int)ans.size());
    rep (i, ans.size()) printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
  }

  return 0;
}

