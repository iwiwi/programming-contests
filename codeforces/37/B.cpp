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


pair<int, pair<int, int> > S[1010];

int main() {
  int N, H, R;
  while (3 == scanf("%d%d%d", &N, &H, &R)) {
    rep (i, N) {
      scanf("%d%d", &S[i].first, &S[i].second.first);
      S[i].second.second = i;
    }
    sort(S, S + N);
    reverse(S, S + N);

    int h = H, d = 0, t, i = 0;
    priority_queue<pair<int, int> > que;
    vector<pair<int, int> > hist;

    for (t = 0; ; ++t) {
      h -= d;
      h = min(H, h + R);
      
      if (h <= 0) break;

      for (; i < N; ++i) {
        if (h * 100 > H * S[i].first) break;
        que.push(S[i].second);
      }
      if (!que.empty()) {
        d += que.top().first;
        hist.pb(mp(t, que.top().second));
        que.pop();
      }
      else {
        if (h == H) goto ng;
      }
    }

    puts("YES");
    printf("%d %d\n", t, (int)hist.size());
    rep (i, hist.size()) printf("%d %d\n", hist[i].first, hist[i].second + 1);
    continue;
  ng:;
    puts("NO");
  }
  
  return 0;
}

