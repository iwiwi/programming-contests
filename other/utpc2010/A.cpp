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
  int N;
  while (1 == scanf("%d", &N)) {

    int ma = 0, mi = 999999;
    rep (i, N) {
      int s = 0;
      rep (j, 5) {
        int a;
        scanf("%d", &a);
        s += a;
      }
      ma = max(ma, s);
      mi = min(mi, s);
    }
    printf("%d %d\n", ma, mi);
  }
  
  return 0;
}

