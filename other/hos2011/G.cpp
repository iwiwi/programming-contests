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

int M, N, A, B;
int X[1000010];
bool Y[1 << 10];

int ps[20];

int rec(int i) {
  if (i == N) {
    rep (j, A) {
      int y = 0;
      rep (k, N) y = y << 1 | (X[j] >> ps[k] & 1);
      if (!Y[y]) return 0;
    }
    return 1;
  } else {
    int res = 0;
    rep (j, M) {
      ps[i] = j;
      res += rec(i + 1);
    }
    return res;
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &M, &N, &A, &B);
    rep (i, A) scanf("%d", &X[i]);
    set<int> use;
    for(int i = 0; i < M; ++i) {
      int cap = (1 << M) - 1;
      bool ok = false;
      for(int j = 0; j < A; ++j) if((X[j] >> i) & 1) {
        cap = min(cap, X[j]);
        ok = true;
      }
      if(ok) use.insert(cap);
    }
    if(A > 0 && X[0] == 0) use.insert(0);
    A = 0;
    for(set<int>::iterator it = use.begin(); it != use.end(); ++it) X[A++] = *it;

    memset(Y, 0, sizeof(Y));
    rep (i, B) {
      int x;
      scanf("%d", &x);
      Y[x] = true;
    }

    int num = rec(0);
    printf("%d\n", num);
  }

  return 0;
}
