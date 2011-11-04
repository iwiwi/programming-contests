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

const int MAX_N = 200010;

struct sa_comp {
  int h, *g;
  sa_comp(int h_, int *g_) : h(h_), g(g_) {}
  bool operator() (int a, int b) {
    return a == b ? false : g[a] != g[b] ? g[a] < g[b] : g[a + h] < g[b + h];
  }
};

int g[MAX_N], b[MAX_N];

void construct_sa(char *s, int n, int *sa) {
  for (int i = 0; i <= n; i++) {
    sa[i] = i;
    g[i] = s[i];
  }
  b[0] = 0;
  b[n] = 0;
  sort(sa, sa + n + 1, sa_comp(0, g));
  for (int h = 1; b[n] != n; h *= 2) {
    sa_comp cmp(h, g);
    sort(sa, sa + n + 1, cmp);
    for (int i = 0; i < n; i++) b[i + 1] = b[i] + cmp(sa[i], sa[i + 1]);
    for (int i = 0; i <= n; i++) g[sa[i]] = b[i];
  }
}

void construct_lcp(char *s, int n, int *sa, int *lcp) {
  int h = 0;
  for (int i = 0; i <= n; i++) b[sa[i]] = i;
  for (int i = 0; i <= n; i++) {
    if (b[i]) {
      for (int j = sa[b[i] - 1]; j + h < n && i + h < n && s[j + h] == s[i + h]; h++);
      lcp[b[i]] = h;
    }
    else lcp[b[i]] = -1;
    if (h > 0) h--;
  }
}



char S[100010];
int sa[100010];
int lcp[100010];

int stki[1000010], stkh[1000010];
ll ans = 0;

int solve(const vector<int> &a) {
  // a.push_back(0);
  assert(a.back() == 0);  // a sentinel must be added

  int stkp = 0, res = 0;
  rep (i, a.size()) {
    int j = i;
    while (stkp > 0 && stkh[stkp - 1] >= a[i]) {
      j = stki[stkp - 1];
      // res = max(res, stkh[stkp - 1] * (i - j));
      if (stkh[stkp - 1] != a[i])  {
        // printf("%d: %d * %d\n", i, stkh[stkp - 1], (i - j));
        ll k = ((i - j) + 1) / 2;

        ll d;
        if (stkp >= 2) d = stkh[stkp - 1] - max(stkh[stkp - 2], a[i]);
        else d = stkh[stkp - 1] - a[i];
        // ll d = stkh[stkp - 1] - a[i];
        // printf(" %d -> %d\n", stkh[stkp - 1], a[i]);
        // printf(" %lld %lld\n", d, k);
        ans += d * (k + 1) * k / 2;
      }
      --stkp;
    }
    stki[stkp] = j;
    stkh[stkp] = a[i];
    ++stkp;
  }
  return res;
}

int main() {
  while (cin >> S) {
    int N = strlen(S);
    construct_sa(S, N, sa);
    construct_lcp(S, N, sa, lcp);

    lcp[0] = 0;
    vector<int> lcp2;
    for (int i = 0; i <= N; ++i) {
      lcp2.pb(lcp[i]);
      lcp2.pb(N - sa[i]);
      // printf(" %d\n %d\n", lcp[i], N - sa[i]);
    }
    lcp2.pb(0);

    ans = 0;
    solve(lcp2);
    cout << ans << endl;
  }

  return 0;
}

