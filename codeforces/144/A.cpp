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
  int N;
  while (1 == scanf("%d", &N)) {
    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);

    int ans = 0;

    int ma = *max_element(all(A));
    rep (i, N) if (A[i] == ma) {
      while (i > 0) {
        swap(A[i - 1], A[i]);
        ++ans;
        --i;
      }
      break;
    }

    int mi = *min_element(all(A));
    int p = -1;
    rep (i, N) if (A[i] == mi) p = i;
    ans += (N - 1) - p;

    printf("%d\n", ans);
  }

  return 0;
}

