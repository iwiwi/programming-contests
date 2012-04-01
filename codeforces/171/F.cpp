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


typedef long long ll;

int len(ll x) {
  int l = 1;
  for (x /= 10; x > 0; x /= 10) l++;
  return l;
}

ll rev(ll x) {
  ll r = 0;
  for (; x > 0; x /= 10) r = r * 10 + x % 10;
  return r;
}
ll pow10(int p) {
  ll r = 1;
  for (; p > 0; p--) r *= 10;
  return r;
}


int main() {
  sieve(1000000);

  vector<int> v;
  rep (i, prime_n) {
    int p = prime[i];
    int r = rev(p);
    if (p != r && !is_composite[r]) v.pb(p);
  }

  int n;
  scanf("%d", &n);
  printf("%d\n", v[n - 1]);

  return 0;
}

