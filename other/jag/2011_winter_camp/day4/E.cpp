#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back

const ll MOD =  1000000007;

int N, T;
int D[1000010];

int main() {
  scanf("%d%d", &N, &T);
  rep (i, N) scanf("%d", &D[i]);
  sort(D, D + N);

  ll crr = 1;
  deque<int> que;
  rep (i, N) {
    while (!que.empty() && D[i] - que.front() > T) que.pop_front();
    crr *= (1 + que.size());
    crr %= MOD;
    que.push_back(D[i]);
  }
  cout << crr << endl;
  return 0;
}
