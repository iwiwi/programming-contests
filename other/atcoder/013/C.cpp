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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)



int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    int gru = 0;
    rep (i, N) {
      int X[3];
      rep (j, 3) scanf("%d", &X[j]);

      int M;
      scanf("%d", &M);
      int mi[3] = {INT_MAX, INT_MAX, INT_MAX};
      int ma[3] = {INT_MIN, INT_MIN, INT_MIN};
      rep (j, M) rep (k, 3) {
        int x;
        scanf("%d", &x);
        mi[k] = min(mi[k], x);
        ma[k] = max(ma[k], x);
      }

      rep (j, 3) {
        gru ^= (mi[j]);
        gru ^= (X[j] - ma[j] - 1);
      }
    }

    puts(gru ? "WIN" : "LOSE");
  }

  return 0;
}

