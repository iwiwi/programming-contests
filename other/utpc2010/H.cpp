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

#include <climits>

typedef long long ll;
#define F first
#define S second

int N, M;
pair<int, int> P[1010];
int Q[1010];
bool done[1010];

ll cnt[1010];

int main() {
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    int y; // waros
    rep (i, N) scanf("%d%d%d", &P[i].F, &y, &P[i].S);
    rep (i, M) scanf("%d", &Q[i]);

    sort(P, P + N);
    sort(Q, Q + M);

    ll ans = 1LL << 50;
    memset(done, 0, sizeof(done));

    while (M > 0) {
      memset(cnt, 0, sizeof(cnt));
      
      int k = 0;
      rep (j, N) {
        while (k + 1 < M && abs(P[j].F - Q[k]) > abs(P[j].F - Q[k + 1])) ++k;
        cnt[k] += P[j].S;
      }

      ll mac = 0, mak = -1;
      rep (k, M) {
        if (cnt[k] > mac) {
          mac = cnt[k];
          mak = k;
        }
      }

      ans = min(ans, mac);
      
      for (int k = mak; k < M; ++k) Q[k] = Q[k + 1];
      --M;
    }

    cout << ans << endl;
  }
  
  return 0;
}

