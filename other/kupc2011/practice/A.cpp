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
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int main() {
  int N, M;
  while (cin >> N >> M) {
    string s[20];
    rep (i, N) cin >> s[i];

    int ans = 0;
    for (int b = 0; b < M; ++b) {
      for (int e = b; e <= M; ++e) {
        string t = s[0].substr(b, e - b);
        rep (i, N) if (s[i].find(t) == string::npos) goto ng;
        ans = max(ans, (int)t.length());
     ng:;
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}

