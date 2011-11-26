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

    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);

    int i = 0;
    while (i < N) {
      if (i) printf(" ");
      
      int j = i + 1;
      while (j < N && A[j] - A[j - 1] == 1) ++j;
      
      if (j == i + 1) printf("%d", A[i]);
      else printf("%d-%d", A[i], A[j - 1]);
      
      i = j;
    }
    puts("");
  }
  return 0;
}

