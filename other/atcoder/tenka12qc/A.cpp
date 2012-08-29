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



int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    sieve(N - 1);
    printf("%d\n", prime_n);
  }

  return 0;
}

