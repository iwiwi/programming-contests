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

int N;
char S[1000010];
int ans[1000010];

int main() {
  while (1 == scanf("%d", &N)) {
    scanf("%s", S);
    int L = 2 * N;

    stack<int> stk;
    rep (i, L) {
      if (stk.empty()) {
        stk.push(i);
        continue;
      }

      int j = stk.top();
      if (S[i] != S[j]) {
        ans[i] = j;
        ans[j] = i;
        stk.pop();
      }
      else {
        stk.push(i);
      }
    }

    rep (i, L) printf("%d\n", ans[i] + 1);
  }
  
  return 0;
}

