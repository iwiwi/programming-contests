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

int cnt[1000010];
int A[50010];

int main() {
  int N, M;
  scanf("%d%d", &N, &M);

  rep (i, N) scanf("%d", &A[i]);

  rep (i, M) {
    char q;
    int x, y;
    scanf(" %c%d%d", &q, &x, &y);

    if (q == 'M') A[x] = y;
    else {
      int ans = 0;
      for (int i = x; i < y; ++i) {
        if (cnt[A[i]]++ == 0) ++ans;
      }
      printf("%d\n", ans);
      for (int i = x; i < y; ++i) {
        --cnt[A[i]];
      }
    }
  }

  return 0;
}

