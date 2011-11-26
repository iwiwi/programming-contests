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


int A[10010], B[10010];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", A + i);
    rep (i, N) scanf("%d", B + i);

    sort(A, A + N);
    sort(B, B + N);
    int an = remove(A, A + N, 0) - A;
    int bn = remove(B, B + N, 0) - B;
    
    while (an > 0 || bn > 0) {
      if (A[an - 1] == bn) {
        rep (i, bn) --B[i];
        bn = remove(B, B + bn, 0) - B;
        --an;
      }
      else if (B[bn - 1] == an) {
        rep (i, an) --A[i];
        an = remove(A, A + an, 0) - A;
        --bn;
      }
      else {
        puts("No");
        goto done;
      }
    }
    puts("Yes");
  done:;
  }
  return 0;
}

