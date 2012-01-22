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


typedef int val_t;

val_t sum(int i, val_t *bit) {
  val_t s = 0;
  for (; i > 0; i -= i & -i) s += bit[i];
  return s;
}

void add(int i, val_t v, val_t *bit, int n) {
  for (; i <= n; i += i & -i) bit[i] += v;
}



int A[10010];
int bit[10010];
int K[10010];

int N, K1, K2, K3;

int solve(int K) {
  vector<int> ss(N + 1, 0);
  rep (i, N) ss[i + 1] = ss[i] + A[i];
  ss.push_back(-100000000);
  sort(all(ss));
  ss.erase(unique(all(ss)), ss.end());

  int lb = - (10000 * 10000 + 10);
  int ub = + (10000 * 10000 + 10);
  while (ub - lb > 1) {
    int X = (lb + ub) / 2;
    int s = 0, c = 0;

    memset(bit, 0, sizeof(bit));
    int k = lower_bound(all(ss), 0) - ss.begin();
    add(k, 1, bit, ss.size());

    rep (i, N) {
      s += A[i];
      {
        int k = lower_bound(all(ss), s - X) - ss.begin();
        c += sum(k - 1, bit);
      }

      {
        int k = lower_bound(all(ss), s) - ss.begin();
        add(k, 1, bit, ss.size());
      }

      if (c > K) {
        lb = X;
        goto done;
      }
    }
    // printf(" %d: %d\n", X, c);

    ub = X;
 done:;
  }
  return ub;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &N, &K1, &K2, &K3);
    rep (i, N) scanf("%d", &A[i]);

    printf("%d %d %d\n", solve(K1 - 1), solve(K2 - 1), solve(K3 - 1));
  }

  return 0;
}

