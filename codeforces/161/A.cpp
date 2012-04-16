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

int N, M, X, Y;
int A[1000010];
int B[1000010];

int main() {
  while (4 == scanf("%d%d%d%d", &N, &M, &X, &Y)) {
    rep (i, N) scanf("%d", A + i);
    rep (j, M) scanf("%d", B + j);

    vector<pair<int, int> > ans;
    int i = 0, j = 0;
    while (i < N && j < M) {
      if (B[j] < A[i] - X) ++j;
      else if (A[i] + Y < B[j]) ++i;
      else {
        ans.pb(mp(i, j));
        ++i;
        ++j;
      }
    }

    printf("%d\n", (int)ans.size());
    rep (i, ans.size()) printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
  }

  return 0;
}

