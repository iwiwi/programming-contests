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

pair<int, int> A[3010];

ll dp[3010];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d%d", &A[i].first, &A[i].second);
    sort(A, A + N);

    dp[0] = A[0].second;
    for (int i = 1; i < N; ++i) {
      // stick
      dp[i] = A[i].second + *min_element(dp, dp + i);

      // don't stick
      rep (j, i) dp[j] += A[i].first - (ll)A[j].first;
    }

    printf("%lld\n", *min_element(dp, dp + N));
  }
  
  return 0;
}

