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

int N, M;
string A[110];
int B[1110];


int main() {
  scanf("%d%d", &N, &M);
  rep (i, N) cin >> A[i] >> B[i];

  int ans = 0;
  rep (i, M) {
    string s;
    cin >> s;
    
    rep (j, N) {
      rep (k, 8) {
        if (A[j][k] != '*' && A[j][k] != s[k]) goto ng;
      }
      ans += B[j];
    ng:;
    }
  }

  printf("%d\n", ans);
  
  return 0;
}

