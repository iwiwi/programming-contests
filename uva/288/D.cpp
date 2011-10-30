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

char buf[1000010];
pair<string, int> ps[100010];
int rev[100010];

int lcp[100010];

const int MAX_N = 100010;
const int MAX_LOGN = 18;

int val[MAX_LOGN][MAX_N];
int idx[MAX_LOGN][MAX_N];

void construct_rmq(int *a, int n) {
  memcpy(val[0], a, sizeof(int) * n);
  for (int i = 0; i < n; i++) idx[0][i] = i;

  int l = 1;
  for (int k = 1; k < n; k *= 2) {
    for (int i = 0; i + k < n; i++) {
      if (val[l - 1][i] <= val[l - 1][i + k]) {
        val[l][i] = val[l - 1][i];
        idx[l][i] = idx[l - 1][i];
      }
      else {
        val[l][i] = val[l - 1][i + k];
        idx[l][i] = idx[l - 1][i + k];
      }
    }
    l++;
  }
}

int rmq(int a, int b) { // [a, b]
  int l = 31 - __builtin_clz(b - a + 1), k = 1 << l, c = b - k + 1;
  return val[l][a] <= val[l][c] ? idx[l][a] : idx[l][c];
}


int main() {
  int T;
  scanf("%d", &T);

  rep (ca, T) {
    int N;
    scanf("%d", &N);
    rep (i, N) {
      scanf("%s", buf);
      ps[i] = mp(string(buf), i);
    }

    sort(ps, ps + N);
    rep (i, N) rev[ps[i].second] = i;

    rep (i, N - 1) {
      int k = 0;
      while (k < ps[i].first.length() && k < ps[i + 1].first.length()) {
        if (ps[i].first[k] != ps[i + 1].first[k]) break;
        ++k;
      }
      // cout << ps[i].first << " " << ps[i + 1].first << " " << k << endl;

      lcp[i] = k;
    }
    construct_rmq(lcp, N - 1);

    printf("Case %d:\n", ca + 1);

    int Q;
    scanf("%d", &Q);
    rep (i, Q) {
      int a, b;
      scanf("%d%d", &a, &b);
      a = rev[a - 1];
      b = rev[b - 1];

      if (a > b) swap(a, b);

      if (a == b) printf("%d\n", (int)ps[a].first.length());
      else {
        printf("%d\n", lcp[rmq(a, b - 1)]);
      }
    }
  }

  return 0;
}

