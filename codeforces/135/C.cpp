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

int L;
char S[100010];
set<string> ans;

void solve() {
  int n0 = count(S, S + L, '0');
  int n1 = count(S, S + L, '1');

  int tm = (L - 2 + 1) / 2;
  int tp = (L - 2) / 2;

  if (n1 <= tm) ans.insert("00");
  if (n0 <= tp) ans.insert("11");
  if (n1 <= tm + 1 && n0 <= tp + 1) {
    int l0 = -1, l1 = -1;
    rep (i, L) {
      if (S[i] == '0') l0 = i;
      if (S[i] == '1') l1 = i;
    }
    if (l0 < l1) ans.insert("01");
    else if (l1 < l0) ans.insert("10");
  }
}

int main() {
  while (1 == scanf("%s", S)) {
    L = strlen(S);
    vector<int> q;
    rep (i, L) if (S[i] == '?') q.pb(i);
    reverse(all(q));
    int k = min(2, (int)q.size());

    ans.clear();
    rep (b, 1 << k) {
      rep (i, k) S[q[i]] = '0' + ((b >> i) & 1);
      solve();
    }
    tr (ans, ite) cout << *ite << endl;
    fprintf(stderr, "--\n");
  }

  return 0;
}

