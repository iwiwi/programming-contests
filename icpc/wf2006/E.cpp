#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <climits>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair
#define pb push_back

typedef long long ll;

int len, A[50];
int dp[50][50][16010];

int search(int pos, int zero, int one) {
  if (zero < 0 || one < 0) return 0;
  if (len - pos < zero) return 0;
  if (one >= 1LL << (len - pos - zero)) return 0;
  
  if (pos == len) return zero == 0 && one == 0 ? 1 : 0;
  if (dp[pos][zero][one] != -1) return dp[pos][zero][one];
  
  // printf("%d %d %d\n", pos, zero, one);

  if (A[pos] == 0) return dp[pos][zero][one] = search(pos + 1, zero - 1, one);
  else {  // A[pos] == 1
    ll x = 0, res = 0;
    for (int to = pos + 1; to <= len; ++to) {
      if (res >= 2) break;
      
      x = (x << 1) + A[to - 1];
      if (to < len && A[to] == 1) continue;
      if (to - pos == 1) res += search(to, zero, one - 1);
      else if (to - pos == 2 && x == 2) continue;
      else if (to - pos == 2 && x == 3) {
	res += search(to, zero, one - 2);
	res += search(to, zero, one - 3);
      } else {
	res += search(to, zero, one - x);
      }
    }
    return dp[pos][zero][one] = res;
  }
}

int main() {
  for (int ca = 1; ; ++ca) {
    int L, N;
    scanf("%d%d", &L, &N);
    if (L == 0 && N == 0) return 0;

    string s;
    cin >> s;
    len = s.length();
    rep (i, len) A[i] = s[i] - '0';

    memset(dp, -1, sizeof(dp));
    int res = search(0, L - N, N);
    printf("Case #%d: %s\n", ca,
	   res == 0 ? "NO" : res == 1 ? "YES" : "NOT UNIQUE");
  }
}
