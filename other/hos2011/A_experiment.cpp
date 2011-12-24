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

const ll MOD = 1000000009;


const int MAX_N = 1000010;

int prime[MAX_N], prime_n;
bool is_composite[MAX_N + 1];

void sieve(int n) {
  is_composite[0] = is_composite[1] = true;
  for (int i = 2; i * i <= n; i++) {
    if (is_composite[i]) continue;
    for (int j = i; i * j <= n; j++) is_composite[i * j] = true;
  }
  prime_n = 0;
  for (int i = 2; i <= n; i++) {
    if (!is_composite[i]) prime[prime_n++] = i;
  }
}



unsigned char pot[MOD];

int main() {
  const int L = 75;

  sieve(150);
  printf("prime: %d\n", prime_n);

  rep (i, MOD) pot[i] = 160;

  queue<int> ques[160];
  ques[0].push(1);
  pot[1] = 0;
  for (int t = 0; t < L; ++t) {
    int cnt = 0;

    while (!ques[t].empty()) {
      ll x = ques[t].front();
      ques[t].pop();
      if (t > pot[x]) continue;

      ++cnt;

      rep (i, prime_n) {
        ll tt = t + prime[i];
        if (tt > L) break;

        ll tx = x * prime[i] % MOD;
        if (tt < pot[tx]) {
          pot[tx] = tt;
          ques[tt].push(tx);
        }
      }
    }

    printf("%d: %d\n", t, cnt);
  }

  ll s = 0;
  rep (i, MOD) if (pot[i] == 160) ++s;

  printf("%lld, %lld\n", s, MOD - s);

  return 0;
}

