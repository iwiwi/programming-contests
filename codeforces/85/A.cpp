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

char ans[10][110];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    memset(ans, 0, sizeof(ans));
    if (N % 2 == 0) {
      rep (i, N / 2) ans[0][i * 2] = ans[0][i * 2 + 1] = 'a' + (i % 2);
      rep (i, N / 2 - 1) ans[1][i * 2 + 1] = ans[1][i * 2 + 2] = 'c' + (i % 2);
      rep (i, N / 2 - 1) ans[2][i * 2 + 1] = ans[2][i * 2 + 2] = 'e' + (i % 2);
      rep (i, N / 2) ans[3][i * 2] = ans[3][i * 2 + 1] = 'g' + (i % 2);
      ans[1][0] = ans[2][0] = 'y';
      ans[1][N - 1] = ans[2][N - 1] = 'z';
    }
    else {
      rep (i, N / 2) ans[0][i * 2] = ans[0][i * 2 + 1] = 'a' + (i % 2);
      rep (i, N / 2) ans[1][i * 2] = ans[1][i * 2 + 1] = 'c' + (i % 2);
      rep (i, N / 2) ans[2][i * 2 + 1] = ans[2][i * 2 + 2] = 'e' + (i % 2);
      rep (i, N / 2) ans[3][i * 2 + 1] = ans[3][i * 2 + 2] = 'g' + (i % 2);
      ans[2][0] = ans[3][0] = 'y';
      ans[0][N - 1] = ans[1][N - 1] = 'z';
    }
    rep (y, 4) printf("%s\n", ans[y]);
  }

  return 0;
}

