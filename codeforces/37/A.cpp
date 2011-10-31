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
    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);

    vector<int> B = A;
    sort(all(B));
    B.erase(unique(all(B)), B.end());

    int ma = 0;
    rep (i, B.size()) ma = max(ma, (int)count(all(A), B[i]));
    printf("%d %d\n", ma, (int)B.size());
  }
  
  
  return 0;
}

