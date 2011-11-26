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

const int N = 100000;
const int M = 25;

double dp[100010][30];
double ans[100010];

int main() {
  dp[0][0] = 1.0;
  for (int n = 0; n < N; ++n) {
    ans[n + 1] += ans[n];
    
    for (int i = 0; i < M; ++i) {
      double p = 1.0 / (1 << i);
      ans[n + 1] += dp[n][i] * p;
      dp[n + 1][i + 1] += dp[n][i] * p;
      dp[n + 1][0] += dp[n][i] * (1.0 - p); 
    }
  }

  for (;;) {
    int n;
    scanf("%d", &n);
    if (!n) return 0;
    printf("%.10f\n", ans[n]);
  }

}

