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

int A[1000010], B[1000010];
int ans[1000010];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", A + i);
    rep (i, N) scanf("%d", B + i);
    rep (i, N) ans[A[i]] = B[i];

    for (int i = 1; i <= N; ++i) printf("%d%c", ans[i], i == N ? '\n' : ' ');
  }

  return 0;
}

