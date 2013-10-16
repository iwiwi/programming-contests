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
  int N;
  while (1 == scanf("%d", &N)) {
    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);
    sort(all(A));

    int need_to_fill = 0, need_to_move = 0;
    rep (i, N) need_to_fill += max(0, 3 - A[i]);
    int total = accumulate(all(A), 0);

    sort(all(A));
    int ans = INT_MAX;
    rep (i, N) {  // [i, N)
      int num_rooms = N - i;
      if (4 * num_rooms >= total && 3 * num_rooms <= total) {  // Possible?
        int tmp = max(need_to_fill, need_to_move);
        ans = min(ans, tmp);
      }

      // Next
      need_to_fill -= max(0, 3 - A[i]);
      need_to_move += A[i];
    }

    if (ans == INT_MAX) puts("-1");
    else printf("%d\n", ans);
  }
}
