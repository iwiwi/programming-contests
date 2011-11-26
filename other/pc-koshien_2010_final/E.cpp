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

int N;
int A[2][110];

const int INF = 987654321;

int mem[2][110];


int main() {
  for (;;) {
    scanf("%d", &N);
    if (N == 0) return 0;
    rep (i, 2) rep (j, N) scanf("%d", &A[i][j]);

    queue<pair<int, int> > que;
    memset(mem, -1, sizeof(mem));

    rep (i, 2) {
      que.push(mp(i, 0));
      mem[i][0] = 0;
    }

    while (!que.empty()) {
      int b = que.front().first;
      int k = que.front().second;
      int c = mem[b][k];
      que.pop();

      while (k + 1 < N && A[b][k] == 1 && A[b][k + 1] == 1) ++k;
      while (k > 0 && A[b][k] == 2) --k;

      if (k == N - 1 && A[b][k] != 2) {
        printf("%d\n", c);
        goto done;
      }

      // printf("%d %d (%d)\n", b, k, c);

      // assert(A[b][k] == 0);
      for (int t = 0; t <= 2; ++t) {
        int tb = 1 - b;
        int tk = k + t;
        if (mem[tb][tk] == -1) {
          que.push(mp(tb, tk));
          mem[tb][tk] = c + 1;
        }
      }
    }

    puts("NA");
 done:;
  }

  return 0;
}

