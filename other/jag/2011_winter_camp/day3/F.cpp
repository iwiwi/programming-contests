#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define mp make_pair
#define pb push_back

typedef long long ll;

int M, N;
int caro[2500010];
int kiwi[2500010];

void gen(int m0, int md, int M, int N, int *out) {
  int x = m0;
  rep (i, M) {
    // printf("%d ", x);
    ++out[x];
    x = (ll(x) * 58 + md) % (N + 1);
  }
  // puts("");
}

int sum, dif, crr;
stack<pair<int, int> > stk;
ll ans;

void doit(int k) {
  // printf("doit: %d\n", k);
  int rest = k - sum;
  while (crr >= 1 && rest > kiwi[crr]) {
    if (kiwi[crr] >= 0) {
      stk.push(mp(crr + dif, kiwi[crr]));
      rest -= kiwi[crr];
      sum += kiwi[crr];
    }
    --crr;
  }
  // printf(" first: %d\n", k - rest);
  ans += (k - rest);
  ++dif;

  while (!stk.empty() && stk.top().first - dif == 0) {
    sum -= stk.top().second;
    stk.pop();
  }
  
  if (crr >= 1 && rest > 0) {
    ans += rest;
    // printf(" second: %d\n", rest);
    kiwi[crr    ] -= rest;
    kiwi[crr - 1] += rest;
  }

  if (!stk.empty() && stk.top().first - dif == crr) {
    kiwi[crr] += stk.top().second;
    sum -= stk.top().second;
    stk.pop();
  }
}

int main() {
  scanf("%d%d", &M, &N);
  int m0, md, n0, nd;
  scanf("%d%d%d%d", &m0, &md, &n0, &nd);
  gen(m0, md, M, N, caro);
  gen(n0, nd, N, M, kiwi);

  crr = M;
  for (int k = 0; k <= N; ++k) {
    rep (i, caro[k]) doit(k);
  }
  printf("%lld\n", ans);

  return 0;
}
