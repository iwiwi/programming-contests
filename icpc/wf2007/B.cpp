#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

int main() {
  for (int ca = 1; ; ++ca) {
    string A;
    cin >> A;
    if (A == "end") return 0;

    int N = A.size();
    vector<int> dp(N);
    rep (i, N) {
      dp[i] = 1;
      rep (j, i) {
        if (A[j] < A[i]) dp[i] = max(dp[i], dp[j] + 1);
      }
    }

    int ans = *max_element(dp.begin(), dp.end());
    printf("Case %d: %d\n", ca, ans);
  }
}
