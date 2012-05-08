#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

int N;

bool doit(vector<pair<int, int> > A, double x) {
  double req = 0.0;
  rep (i, N) {
    double t = max(req, (double)A[i].first);
    if (t > A[i].second) return false;
    req = t + x;
  }
  return true;
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d", &N);
    if (N == 0) return 0;
    
    vector<pair<int, int> > A(N);
    rep (i, N) scanf("%d%d", &A[i].first, &A[i].second);
    sort(A.begin(), A.end());

    double ans = 0.0;
    do {
      if (doit(A, ans) == true) {
        double lb = ans, ub = 10000;
        rep (iter, 100) {
          double x = (lb + ub) / 2;
          if (doit(A, x)) lb = x;
          else ub = x;
        }
        ans = lb;
      }
    } while (next_permutation(A.begin(), A.end()));

    int s = (int)round(ans * 60);
    int m = s / 60;
    s %= 60;
    printf("Case %d: %d:%02d\n", ca, m, s);
  }
}
