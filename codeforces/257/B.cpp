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

// Petya, -Vasya
pair<int, int> solve(int n, int m) {
  int r[2] = {n - 1, m};
  int prv = 0;

  int p = 0, v = 0;
  for (int i = 1; r[0] + r[1]; ++i) {
    int nxt = 0;
    if (i % 2 == 0) {
      // Petya
      if (r[prv]) nxt = prv;
      else nxt = 1 - prv;
    } else {
      // Vasya
      if (r[1 - prv]) nxt = 1 - prv;
      else nxt = prv;
    }
    if (prv == nxt) ++p;
    else ++v;

    --r[nxt];
    prv = nxt;
  }

  return mp(p, -v);
}

int main() {
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    pair<int, int> ans = max(solve(N, M), solve(M, N));
    printf("%d %d\n", ans.first, -ans.second);
  }

  return 0;
}

