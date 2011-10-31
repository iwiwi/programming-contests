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

ll sum(int i, ll *bit) {
  ll s = 0;
  for (; i > 0; i -= i & -i) s += bit[i];
  return s;
}

void add(int i, int v, ll *bit, int n) {
  for (; i <= n; i += i & -i) bit[i] += v;
}




int rad[200010];

int manacher(char *text, int n) {
  int i, j, k;
  for (i = 0, j = 0; i < 2*n; i += k, j = max(j-k, 0)) {
    while (i-j >= 0 && i+j+1 < 2*n && text[(i-j)/2] == text[(i+j+1)/2]) ++j;
    rad[i] = j;
    for (k = 1; i-k >= 0 && rad[i]-k >= 0 && rad[i-k] != rad[i]-k; ++k)
      rad[i+k] = min(rad[i-k], rad[i]-k);
  }

  return *max_element(rad, rad + 2*n);
}


char text[100010];
ll bit[200010];

int main() {
  int cases;
  scanf("%d", &cases);
  rep (ca, cases) {
    scanf("%s", text);
    int L = strlen(text);
    manacher(text, L);

    int M = L * 2 - 3;
    // if (M >= 1 && M + rad[M] >= L * 2) --rad[M];

    vector<pair<int, int> > evt;
    for (int i = 1; i <= M; i += 2) {
      int r = rad[i];
      // printf("rad[%d] = %d\n", i, r);
      evt.pb(mp(i - r / 2, -i));
      evt.pb(mp(i, i));
    }

    memset(bit, 0, sizeof(bit));
    sort(all(evt));
    int evt_p = 0;
    ll ans = 0, tot = 0;
    for (int i = 1; i <= M; i += 2) {
      while (evt_p < (int)evt.size() && evt[evt_p].first <= i) {
        int k = evt[evt_p].second;
        int s = k < 0 ? -1 : 1;


        k = abs(k);
        ans += s * (tot - sum(k - 1, bit));
        evt_p++;
        // printf("%d: event of %d: %lld - %lld\n", i, k, tot, sum(k - 1, bit));
      }
      ++tot;
      add(i + rad[i], 1, bit, M);
      // printf("%d: add at %d\n", i, i + rad[i]);
    }

    // printf("%lld\n", ans);
    cout << ans << endl;
  }

  return 0;
}

