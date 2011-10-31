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

int N, M, K, T;
pair<int, int> W[110];

int main() {
  scanf("%d%d%d%d", &N, &M, &K, &T);
  rep (i, K) scanf("%d%d", &W[i].first, &W[i].second);
  sort(W, W + K);

  rep (t, T) {
    int i, j;
    scanf("%d%d", &i, &j);

    int k = lower_bound(W, W + K, mp(i, j)) - W;
    if (W[k] == mp(i, j)) {
      puts("Waste");
    }
    else {
      ll tot = M * ll(i - 1) + (j - 1);
      ll cnt = tot - k;
      static const char *names[] = { "Carrots", "Kiwis", "Grapes" };
      puts(names[cnt % 3]);
    }

  }

  return 0;
}

