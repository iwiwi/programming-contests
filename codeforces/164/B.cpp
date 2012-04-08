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

int NA, A[2000010];
int NB, B[1000010];

int revB[1000010];

int main() {
  while (2 == scanf("%d%d", &NA, &NB)) {
    rep (i, NA) { scanf("%d", &A[i]); A[NA + i] = A[i]; }
    memset(revB, -1, sizeof(revB));
    rep (i, NB) { scanf("%d", &B[i]); revB[B[i]] = i; }

    deque<ll> que;
    int ri = 0, ans = 0;
    rep (li, NA) {
      // [li, ri) is in the queue
      ri = max(ri, li);

      while (ri < li + NA) {
        ll p = revB[A[ri]];
        if (p == -1) break;  // no such value in B!

        ll b = que.empty() ? -1 : que.back();
        if (p <= b) {
          ll s = b - p;
          ll k = s / NB + (s % NB ? 1 : 0);
          p += k * NB;
        }
        if (!que.empty() && p - que.front() >= NB) break;
        ++ri;
        que.push_back(p);
      }

      ans = max(ans, ri - li);
      if (revB[A[li]] != -1) que.pop_front();
    }

    printf("%d\n", ans);
  }

  return 0;
}

