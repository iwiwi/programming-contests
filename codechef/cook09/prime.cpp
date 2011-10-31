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


const int MAX_N = 1000010;

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
  sieve(MAX_N);

  for (;;) {
    int n;
    scanf("%d", &n);
    if (n == 0) break;

    for (int i = 0; i < prime_n; ++i) {
      int p3 = prime[i];
      if (p3 * p3 * p3 > n) break;
      for (int j = 0; j < prime_n; ++j) {
        int p2 = prime[j];
        if (p3 * p3 * p3 + p2 * p2 > n) break;

        int p1 = n - p3 * p3 * p3 - p2 * p2;
        if (isn_prime[p1] == false) {
          printf("%d %d %d\n", p1, p2, p3);
          goto done;
        }
      }
    }
    puts("0 0 0");
 done:;
  }

  return 0;
}

