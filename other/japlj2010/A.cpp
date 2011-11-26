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
  int P;
  while (1 == scanf("%d", &P)) {
    if (P == 0) {
      // puts("-1");  // !?
      puts("1 2.0");
    }
    else if (P == 1) {
      puts("1 1.0");
    }
    else {
      int k;
      for (k = 1; (P & (1 << k)) == 0; ++k);
      
      if (__builtin_popcount(P) == 1) {
        printf("%d 0.5\n", k);
      }
      else if (__builtin_popcount(P) == 2 && (P & 1) == 1) {
        printf("%d 0.0\n", k + 1);
      }
      else {
        puts("-1");
      }
    }
  }
  
  return 0;
}

