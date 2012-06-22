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

int N, K;
char F[2][100010];

int pot[2][100010];

int main() {
  while (2 == scanf("%d%d", &N, &K)) {
    rep (x, 2) scanf("%s", F[x]);

    int dx[3] = { 0, 0,  1};
    int dy[3] = {+1, -1, K};

    memset(pot, -1, sizeof(pot));
    queue<pair<int, int> > que;
    que.push(mp(0, 0));
    pot[0][0] = 0;

    while (!que.empty()) {
      int x = que.front().first;
      int y = que.front().second;
      que.pop();

      int t = pot[x][y];
      if (y < t) continue;  // water

      rep (i, 3) {
        int tx = x ^ dx[i];
        int ty = y + dy[i];
        if (ty >= N) goto ok;
        if (F[tx][ty] == 'X' || pot[tx][ty] != -1) continue;
        pot[tx][ty] = t + 1;
        que.push(mp(tx, ty));
      }
    }

    puts("NO");
    continue;
 ok:
    puts("YES");
  }

  return 0;
}

