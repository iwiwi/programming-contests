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

int N, A[60], P;
map<ll, double> mem;

double search(ll b, int s) {
  if (mem.count(b)) return mem[b];

  double res = 0.0;
  int div = 0;

  int prv_a = -1;
  double prv_r = 0;
  rep (i, N) if (~b & (1LL << i)) {
    if (A[i] == prv_a) {
      res += prv_r;
    } else {
      int ts = s + A[i];
      if (ts <= P) {
        prv_a = A[i];
        prv_r = 1 + search(b | (1LL << i), ts);
        res += prv_r;
      }
    }
    div += 1;
  }

  return mem[b] = (div == 0 ? 0.0 : res / div);
}

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", &A[i]);
    scanf("%d", &P);

    sort(A, A + N);
    mem.clear();
    printf("%.10f\n", search(0, 0));
  }

  return 0;
}
