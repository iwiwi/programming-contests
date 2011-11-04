#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <cstring>
#include <climits>
#include <sstream>
#include <stack>
#include <bitset>
#include <queue>
#include <functional>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef pair<pair<int, int>, pair<int, int> > piiii;

int N, M, best;
int adj[40][40];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &M);

    rep (i, N) rep (j, N) scanf("%d", &adj[i][j]);

    priority_queue<piiii> que;
    que.push(mp(mp(0, 0), mp(0, 0)));
    for (;;) {
      int h = que.top().F.F;
      int c = que.top().F.S;
      int k = que.top().S.F;
      int b = que.top().S.S;
      que.pop();

      // printf("[%d, %d, %d, ", h, c, k); cout << bitset<5>(b) << "]" << endl;

      if (k == N) {
        printf("%d\n", c);
        break;
      }

      rep (d, 2) {
        int tc = c, tb = b | (d << k);
        rep (i, k) tc += 2 * adj[i][k] * (d == ((b >> i) & 1) ? 1 : -1);

        int th = tc;
        for (int j = k + 1; j < N; ++j) {
          int s = INT_MIN;
          rep (d2, 2) {
            int t = 0;
            for (int i = 0    ; i <= k; ++i) t += 2 * adj[i][j] * (d2 == ((tb >> i) & 1) ? 1 : -1);
            for (int i = k + 1; i <  N; ++i) t += min(adj[i][j], -adj[i][j]);
            s = max(s, t);
          }
          th += s;
        }

        que.push(mp(mp(th, tc), mp(k + 1, tb)));
      }
    }

  }

  return 0;
}
