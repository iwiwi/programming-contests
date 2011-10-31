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
  int N, A[110];
  scanf("%d", &N);
  rep (i, N) scanf("%d", A + i);

  pair<int, int> res = mp(999999, -1);
  rep (i, N) {
    int d = abs(A[i] - A[(i + 1) % N]);
    res = min(res, mp(d, i));
  }

  printf("%d %d\n", res.second + 1, (res.second + 1) % N + 1);
  
  return 0;
}

