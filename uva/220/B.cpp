#include <cstdio>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)


int main() {
  int cases;
  scanf("%d", &cases);
  rep (ca, cases) {
    int R, C, M, N;
    scanf("%d%d%d%d", &R, &C, &M, &N);

    int cnt[256] = {};
    rep (i, R) rep (j, C) {
      char c;
      scanf(" %c", &c);
      cnt[int(c)]++;
    }

    int ma = *max_element(cnt, cnt + 256);
    int ans = 0;
    for (int c = 'A'; c <= 'Z'; ++c) {
      ans += cnt[c] * (cnt[c] == ma ? M : N);
    }
    printf("Case %d: %d\n", ca + 1, ans);
  }
}
