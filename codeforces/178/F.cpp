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
string A[2010];
int lcp[2010];

int mem_next[2010][2010];
int mem[2010][2010];

int next(int l, int r) {
  if (mem_next[l][r] != -1) return mem_next[l][r];

  assert(r - l >= 2);
  int min_lcp = INT_MAX;
  int min_p = -1;

  for (int p = l + 1; p < r; ++p) {
    if (lcp[p] < min_lcp) {
      min_lcp = lcp[p];
      min_p = p;
    }
  }
  return mem_next[l][r] = min_p;
}

int loop = 0;

int search(int l, int r, int k) {
  if (k < 0 || k > r - l) return -98765432;
  if (r - l == 1) return 0;

  int p = next(l, r);
  if (mem[p][k] != -1) return mem[p][k];

  int x = lcp[p];
  int ans = 0;

  for (int tk = max(0, k - (r - p)); tk <= min(k, p - l); ++tk) {
    int tmp = search(l, p, tk) + search(p, r, k - tk);
    tmp += tk * (k - tk) * x;
    ans = max(ans, tmp);

  }

  return mem[p][k] = ans;
}


int main() {
  while (cin >> N >> K) {
    rep (i, N) cin >> A[i];
    sort(A, A + N);

    rep (i, N - 1) {
      int k = 0;
      while (k < (int)A[i].length() && k < (int)A[i + 1].length() && A[i][k] == A[i + 1][k]) ++k;
      lcp[i + 1] = k;
      // printf("lcp[%d] = %d\n", i, k);
    }

    memset(mem_next, -1, sizeof(mem_next));
    memset(mem, -1, sizeof(mem));
    int ans = search(0, N, K);
    printf("%d\n", ans);

    // fprintf(stderr, "loop: %d\n", loop);
    // fprintf(stderr, "\n--\n");
  }

  return 0;
}

