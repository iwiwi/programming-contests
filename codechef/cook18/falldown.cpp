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

int H, W, L;
int A[2100][2100];

int come[2100];
int movr[2100], movl[2100];
int ls[2100], rs[2100];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &H, &W, &L);
    if (L == 1) rep (y, H) rep (x, W) scanf("%d", &A[y][x]);
    else {
      int X, P, Q, M;
      scanf("%d%d%d%d", &X, &P, &Q, &M);
      ll cur = X;
      rep (y, H) rep (x, W) {
        cur = (cur * P + Q) % M;
        A[y][x] = X - cur;
      }
    }

    memset(come, 0, sizeof(come));
    rep (y, H) {
      for (int s = 0, x = 0; x < W; ++x) {
        ls[x] = s;
        s = max(0, s + A[y][x]);
      }
      for (int s = 0, x = W - 1; x >= 0; --x) {
        rs[x] = s;
        s = max(0, s + A[y][x]);
      }

      for (int x = 0; x < W; ++x) {
        movr[x] = come[x] + A[y][x] + ls[x];
        if (x - 1 >= 0) movr[x] = max(movr[x], movr[x - 1] + A[y][x]);
      }
      for (int x = W - 1; x >= 0; --x) {
        movl[x] = come[x] + A[y][x] + rs[x];
        if (x + 1 < W)  movl[x] = max(movl[x], movl[x + 1] + A[y][x]);
      }

      for (int x = 0; x < W; ++x) {
        come[x] = max(movr[x] + rs[x], movl[x] + ls[x]);
        // printf("%d ", come[x]);
      }
      // puts("");
    }

    printf("%d\n", *max_element(come, come + W));
  }

  return 0;
}

