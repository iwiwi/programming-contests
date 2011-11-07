#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

int N, msk[110];
ll L[110];

ll mem[1 << 16];

ll search(int b) {
  if (mem[b] != -1) return mem[b];
  ll res = 0;
  rep (i, N) {
    if ((b & msk[i]) == msk[i]) {
      res = max(res, L[i] + search(b - msk[i]));
    }
  }
  return mem[b] = res;
}

int main() {
  for (;;) {
    scanf("%d", &N);
    if (N == 0) return 0;

    rep (i, N) {
      int m;
      scanf("%d%lld", &m, &L[i]);

      msk[i] = 0;
      rep (j, m) {
        int s, e;
        scanf("%d%d", &s, &e);
        s -= 6;
        e -= 6;
        for (int k = s; k < e; ++k) msk[i] |= 1 << k;
      }
    }

    memset(mem, -1, sizeof(mem));
    printf("%lld\n", search((1 << 16) - 1));
  }
}
