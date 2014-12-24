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
#define eb(e) emplace_back(e)
#define mp(a, b) make_pair(a, b)

int main() {
  int T;
  scanf("%d", &T);
  rep (t, T) {
    string C, F;
    cin >> C >> F;
    int c = C.length(), f = F.length();

    int n = c + f;

    if (c == f) {
      puts("-1");
    } else {
      int ans = INT_MAX;

      for (int a = 0; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
          int tc = c < a ? c : a + (c % b);
          int tf = f < a ? f : a + (f % b);
          if (tc != tf) {
            ans = min(ans, a + b);
          }
        }
      }
      printf("%d\n", ans);
    }
  }
}
