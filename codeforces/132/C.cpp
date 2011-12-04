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

const int INF = 987654;

int M;
char C[110];

bool vis[110][60][2];
int mem[110][60][2];

int search(int i, int n, bool f) {
  if (n < 0) return -INF;
  if (i == M) {
    if (n % 2 == 0) return 0;
    else return -INF;
  }
  if (vis[i][n][f]) return mem[i][n][f];

  // F
  int res = -INF;
  {
    int tn = n - (C[i] == 'F' ? 0 : 1);
    int tr = (f ? 1 : -1) + search(i + 1, tn, f);
    res = max(res, tr);
  }
  // T
  {
    int tn = n - (C[i] == 'T' ? 0 : 1);
    int tr = search(i + 1, tn, !f);
    res = max(res, tr);
  }

  vis[i][n][f] = true;
  return mem[i][n][f] = res;
}

int main() {
  int N;
  while (2 == scanf("%s%d", C, &N)) {
    M = strlen(C);
    memset(vis, 0, sizeof(vis));
    printf("%d\n", max(search(0, N, true), search(0, N, false)));
  }

  return 0;
}

