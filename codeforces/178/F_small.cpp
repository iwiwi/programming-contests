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

int N, K;
string A[110];

int compute_lcp(const string &a, const string &b) {
  int k = 0;
  while (k < (int)a.length() && k < (int)b.length() && a[k] == b[k]) ++k;
  return k;
}

int main() {
  while (cin >> N >> K) {
    rep (i, N) cin >> A[i];
    sort(A, A + N);

    int score[30][30];
    rep (i, N) rep (j, N) score[i][j] = compute_lcp(A[i], A[j]);

    int ans = 0;
    for (int m = (1 << K) - 1; m < (1 << N); ) {
      int tmp = 0;
      rep (i, N) if (m & (1 << i)) {
        rep (j, i) if (m & (1 << j)) {
          tmp += score[i][j];
        }
      }
      ans = max(ans, tmp);

      int x = m & -m;
      int y = m + x;
      m = ((m & ~y) / x >> 1) | y;
    }

    printf("%d\n", ans);
  }

  return 0;
}

