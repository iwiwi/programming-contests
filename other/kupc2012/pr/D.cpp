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

int A[1010][1010];
int B[1010][1010];
int C[1010][1010];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    rep (i, N) rep (j, N) scanf("%d", &A[i][j]);
    rep (i, N) rep (j, N) scanf("%d", &B[i][j]);
    rep (i, N) rep (j, N) scanf("%d", &C[i][j]);
    rep (i, N) rep (k, N) rep (j, N) C[i][j] -= A[i][k] * B[k][j];

    rep (i, N) rep (j, N) if (C[i][j]) goto no;
    puts("YES");
    continue;
 no:
    puts("NO");
  }

  return 0;
}

