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
  int N, M, K;
  while (3 == scanf("%d%d%d", &N, &M, &K)) {
    map<int, int> A;
    int k;
    rep (i, N) { scanf("%d", &k); ++A[k]; }
    rep (i, M) { scanf("%d", &k); --A[k]; }

    vector<pair<int, int> > B(all(A));
    reverse(all(B));
    int s = 0;
    rep (i, B.size()) {
      s += B[i].second;
      if (s > 0) goto yes;
    }
    puts("NO");
    continue;
 yes:
    puts("YES");
  }

  return 0;
}

