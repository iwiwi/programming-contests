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

int N, MAXB, T, B[1000010];

int max_by(int i, int *bit) {  // [1, i]
  int s = 0;
  for (; i > 0; i -= i & -i) s = max(s, bit[i]);
  return s;
}

void increase(int i, int v, int *bit, int n) {
  for (; i <= n && bit[i] < v; i += i & -i) {
    bit[i] = v;
  }
}

int bit[1000010];

void solve() {
  rep (i, N) scanf("%d", &B[i]);

  map<int, int> ma;
  rep (i, N) ma[B[i]] = 0;
  int K = 1;
  tr (ma, ite) ite->second = K++;
  rep (i, N) B[i] = ma[B[i]];

  T = min(T, min(N, MAXB));

  memset(bit, 0, sizeof(bit));
  rep (i, T) rep (i, N) {
    int t = 1 + max_by(B[i] - 1, bit);
    increase(B[i], t, bit, N);
  }
  printf("%d\n", max_by(N, bit));
}

int main() {
  int num_cases;
  while (4 == scanf("%d%d%d%d", &num_cases, &N, &MAXB, &T)) {
    rep (case_id, num_cases) solve();
  }

  return 0;
}

