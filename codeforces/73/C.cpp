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

const int INF = 987654321;

char S[110];
int L;
int bonus[30][30];

bool vis[110][110][30];
int mem[110][110][30];

int search(int p, int k, int l) {
  if (k < 0) return -INF;
  if (p == L) return 0;
  if (vis[p][k][l]) return mem[p][k][l];

  int res = -INF;
  rep (c, 26) {
    res = max(res, bonus[l][c] + search(p + 1, k - (S[p] == 'a' + c ? 0 : 1), c));
  }

  vis[p][k][l] = true;
  return mem[p][k][l] = res;
}

int main() {
  int K;
  while (2 == scanf("%s%d", S, &K)) {
    L = strlen(S);

    int N;
    scanf("%d", &N);

    memset(bonus, 0, sizeof(bonus));
    rep (i, N) {
      char a, b;
      scanf(" %c %c", &a, &b);
      scanf("%d", &bonus[a - 'a'][b - 'a']);
    }

    memset(vis, 0, sizeof(vis));
    printf("%d\n", search(0, K, 26));
  }

  return 0;
}

