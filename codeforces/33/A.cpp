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

const int INF = 987654321;

int main() {
  int M, N, K;
  while (3 == scanf("%d%d%d", &M, &N, &K)) {
    int via[1010];
    rep (i, N) via[i] = INF;
    rep (i, M) {
      int r, c;
      scanf("%d%d", &r, &c);
      --r;
      via[r] = min(via[r], c);
    }

    ll tot = 0;
    rep (i, N) tot += via[i];
    printf("%d\n", (int)min(tot, (ll)K));
  }
  
  return 0;
}


