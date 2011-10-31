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

const int MAX_N = 2000010;

int prime[MAX_N], prime_n;
bool isn_prime[MAX_N + 1]; // false: 素数

void sieve(int n) {
  isn_prime[0] = isn_prime[1] = true;
  for (int i = 2; i * i <= n; i++) {
    if (isn_prime[i]) continue;
    for (int j = i; i * j <= n; j++) isn_prime[i * j] = true;
  }
  prime_n = 0;
  for (int i = 2; i <= n; i++) {
    if (!isn_prime[i]) prime[prime_n++] = i;
  }
}

int main() {
  sieve(2000000);

  int N, X;
  while (2 == scanf("%d%d", &N, &X)) {
    set<int> A;
    rep (i, N) {
      int a;
      scanf("%d", &a);
      A.insert(a);
    }

    if (X == 2) {
      puts("0");
      continue;
    }

    if (A.count(1)) {
      puts("1");
      continue;
    }

    if (X >= 2000000) {
      goto ng;
    }

    {
      int ans = 0;
      rep (i, prime_n) {
        int p = prime[i];
        if (p >= X) continue;
        if (A.count(p) == 0) goto ng;
        ++ans;
      }
      printf("%d\n", ans);
    }

    continue;
 ng:
    puts("-1");
  }


  return 0;
}

