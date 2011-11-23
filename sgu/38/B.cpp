#include <cstdio>
#include <algorithm>
#include <utility>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define mp make_pair

typedef long long ll;

int N, D;
int X[200010], W[200010];
pair<int, int> ma[200010];

int main() {
  scanf("%d%d", &N, &D);
  rep (i, N) scanf("%d%d", &X[i], &W[i]);

  ma[N] = mp(INT_MIN, -1);
  for (int i = N - 1; i >= 0; --i) {
    ma[i] = max(mp(W[i], i), ma[i + 1]);
  }

  int j = 0;
  pair<int, pair<int, int> > ans = mp(-1, mp(-2, -2));
  rep (i, N) {
    while (j < N && X[j] - X[i] < D) ++j;
    if (j < N) {
      ans = max(ans, mp(W[i] + ma[j].first, mp(i, ma[j].second)));
    }
  }

  printf("%d %d\n", ans.second.first + 1, ans.second.second + 1);
  return 0;
}
