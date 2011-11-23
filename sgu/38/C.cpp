#include <cstdio>
#include <algorithm>
#include <utility>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef long long ll;

int N;
vector<pair<int, pair<int, int> > > hor, ver;  // hor: -, ver: |

int main() {
  while (1 == scanf("%d", &N) && N) {
    hor.clear();
    ver.clear();
    rep (i, N) {
      int x1, y1, x2, y2;
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      if (x1 == x2) ver.pb(mp(x1, mp(min(y1, y2), max(y1, y2))));
      else          hor.pb(mp(y1, mp(min(x1, x2), max(x1, x2))));
    }

    if (ver.size() > hor.size()) ver.swap(hor);
    sort(ver.begin(), ver.end());
    sort(hor.begin(), hor.end());

    ll ans = 0;
    rep (ri, ver.size()) {
      int rx = ver[ri].F;
      rep (li, ri) {
        int lx = ver[li].F;

        int min_y = max(ver[li].S.F, ver[ri].S.F);
        int max_y = min(ver[li].S.S, ver[ri].S.S);
        if (min_y >= max_y) continue;

        int cnt = 0;
        rep (hi, hor.size()) {
          if (min_y <= hor[hi].F && hor[hi].F <= max_y &&
              hor[hi].S.F <= lx && rx <= hor[hi].S.S) {
            ++cnt;
          }
        }

        // printf("%d - %d: %d\n", lx, rx, cnt);
        ans += cnt * (cnt - 1) / 2;
      }
    }

    cout << ans << endl;
  }

  return 0;
}
