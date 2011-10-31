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
    --N;
    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);
    int s, t;
    scanf("%d%d", &s, &t);
    --s;
    --t;
    
    int res = 0;
    for (int i = s; i < t; ++i) res += A[i];
    printf("%d\n", res);
  }
  
  return 0;
}

