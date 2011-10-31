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




int main() {
  for (;;) {
    int L, W, x, y, R, a, v, s;
    cin >> L >> W >> x >> y >> R >> a >> v >> s;
    if (L == 0) break;

    // L - 2R, W - 2R
    x -= R;
    y -= R;

    double tx = x + cos(a / 180.0 * M_PI) * v * s;
    double ty = y + sin(a / 180.0 * M_PI) * v * s;

    double tl = L - 2 * R;
    double tw = W - 2 * R;

    double sx = fmod(tx, tl * 2);
    double sy = fmod(ty, tw * 2);
    if (sx < 0) sx += tl * 2;
    if (sy < 0) sy += tw * 2;
    if (sx > tl) sx = tl * 2 - sx;
    if (sy > tw) sy = tw * 2 - sy;

    printf("%.2f %.2f\n", sx + R, sy + R);
  }

  return 0;
}

