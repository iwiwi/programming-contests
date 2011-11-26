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

const int MAX_N = 10000010;

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
  sieve(10000000);
  vector<int> qs;
  for (int i = 13; i <= 10000000; ++i) {
    if (!isn_prime[i] && !isn_prime[i - 2] && !isn_prime[i - 6] && !isn_prime[i - 8]) {
      qs.pb(i);
    }
  }

  for (;;) {
    int x;
    scanf("%d", &x);
    if (x == 0) return 0;
    iter(qs) ite = upper_bound(all(qs), x);
    --ite;
    printf("%d\n", *ite);
  }

  return 0;
}

