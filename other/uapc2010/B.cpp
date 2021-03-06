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
    int N;
    scanf("%d", &N);
    if (!N) return 0;

    vector<pair<int, int> > A(N);
    rep (i, N) scanf("%d%d", &A[i].second, &A[i].first);
    sort(all(A));

    int s = 0;
    rep (i, N) {
      s += A[i].second;
      if (s > A[i].first) goto no;
    }
    puts("Yes");
    continue;
  no:
    puts("No");
  }
  
  return 0;
}

