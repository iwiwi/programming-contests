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

int main() {
  string S;
  while (cin >> S) {
    int N = S.length();

    int ans = N;
    rep (b, 1 << N) {
      int m = 0;
      rep (i, N) if (b & (1 << i)) {
        rep (j, N) m |= (S[(i + j) % N] == 'o') << j;
      }
      if (m == (1 << N) - 1) ans = min(ans, __builtin_popcount(b));
    }
    printf("%d\n", ans);
  }


  return 0;
}

