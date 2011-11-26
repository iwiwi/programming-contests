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

int N;
vector<int> adj[100010];
vector<int> wgh[100010];

bool done[100010];

int main() {
  for (;;) {
    scanf("%d", &N);
    if (!N) return 0;

    rep (i, N) {
      adj[i].resize(2);
      wgh[i].resize(2);
      rep (j, 2) scanf("%d%d", &adj[i][j], &wgh[i][j]);
    }

    /*
    rep (i, N) {
      rep (j, 2) {
        int k = adj[i][j], w = wgh[i][j];
        rep (l, 2) {
          if (adj[k][l] == i && wgh[k][l] == w) goto ok;
        }
        for (;;) puts("assertion failed");
      ok:;
      }
    }
    */

    memset(done, 0, sizeof(done));
    ll ans = 1;
    rep (i, N) if (!done[i]) {
      int k = i, p = -1;
      ll mw = -999, mc = 1;
      
      while (!done[k]) {
        done[k] = true;
        // printf("%d: %d\n", i, k);
        
        rep (j, 2) if (adj[k][j] != p) {
          if (wgh[k][j] > mw) {
            mw = wgh[k][j];
            mc = 1;
          }
          else if (wgh[k][j] == mw) ++mc;
          p = k;
          k = adj[k][j];
          goto done;
        }
        break;
      done:;
      }
      // printf(" %d %d %d\n", i, mw, mc);

      ans *= mc;
      ans %= 10007;
    }

    printf("%lld\n", ans);
  }
}

