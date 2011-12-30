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
    int A[110], c[2] = {0, 0};
    rep (i, N) {
      scanf("%d", &A[i]);
      ++c[A[i] % 2];
    }

    int s;
    if (c[0] == 1) s = 0;
    else s = 1;
    rep (i, N) if (A[i] % 2 == s) printf("%d\n", i + 1);
  }
  
  return 0;
}
