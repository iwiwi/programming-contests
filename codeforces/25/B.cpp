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
    char A[110];
    scanf("%s", A);

    int i;
    if (N % 3 == 0) {
      i = 0;
    }
    else if (N % 3 == 1) {
      printf("%c%c-%c%c", A[0], A[1], A[2], A[3]);
      i = 4;
    }
    else {
      printf("%c%c", A[0], A[1]);
      i = 2;
    }

    while (i < N) {
      if (i > 0) putchar('-');
      printf("%c%c%c", A[i], A[i + 1], A[i + 2]);
      i += 3;
    }
    puts("");
  }
  
  return 0;
}
