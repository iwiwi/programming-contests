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

char S[1000010];

ll cnt[8];

int main() {
  scanf("%s", S);
  int L = strlen(S);

  ll ans = count(S, S + L, '0');

  if (S[0] != '0') cnt[0] = 1;
  int t = 0;
  rep (i, L) {
    ll tmp[8] = {0};
    rep (m, 8) tmp[m * 10 % 8] += cnt[m];

    t = (t * 10 + (S[i] - '0')) % 8;
    ans += tmp[t];
    if (i + 1 < L && S[i + 1] != '0') ++tmp[t];

    rep (m, 8) cnt[m] = tmp[m];
  }

  cout << ans << endl;

  return 0;
}

