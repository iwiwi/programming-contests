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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

#define F first
#define S second

int W, H;
int fld[110][110];

typedef pair<int, int> pii;
typedef pair<pii, pii> ppiipii;

bool ok(pii p) {
  return fld[p.S][p.F] == 0;
}

int main() {
  for (;;) {
    scanf("%d%d", &W, &H);
    if (W == 0 && H == 0) return 0;

    int tx, ty, kx, ky;
    scanf("%d%d%d%d", &tx, &ty, &kx, &ky);

    memset(fld, 1, sizeof(fld));
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        scanf("%d", &fld[y][x]);
      }
    }

    map<ppiipii, int> mem;
    queue<ppiipii> que;
    mem.insert(mp(mp(mp(tx, ty), mp(kx, ky)), 0));
    que.push(mp(mp(tx, ty), mp(kx, ky)));

    while (!que.empty()) {
      pii t = que.front().F;
      pii k = que.front().S;
      int c = mem[que.front()];
      que.pop();
      if (t == k) {
        printf("%d\n", c);
        goto done;
      }

      rep (d, 4) {
        pii nt = mp(t.F + dx[d          ], t.S + dy[d          ]);
        pii nk = mp(k.F + dx[(d + 2) % 4], k.S + dy[(d + 2) % 4]);

        if (!ok(nt)) nt = t;
        if (!ok(nk)) nk = k;

        if (nt > nk) swap(nt, nk);
        if (mem.count(mp(nt, nk))) continue;
        mem[mp(nt, nk)] = c + 1;
        que.push(mp(nt, nk));
      }
    }
    puts("NA");
  done:;
  }

  return 0;
}

