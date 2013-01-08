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

int main() {
  while (1 == scanf("%d", &N)) {
    vector<double> A;
    rep (i, N) {
      double x, y;
      scanf("%lf%lf", &y, &x);
      A.pb(atan2(y, x));
      A.pb(atan2(y, x) + 2 * M_PI);
    }
    sort(all(A));

    double ma_d = 0.0;
    rep (i, A.size() - 1) {
      ma_d = max(ma_d, A[i + 1] - A[i]);
    }
    printf("%.10f\n", 360.0 - ma_d / M_PI * 180.0);
  }



  return 0;
}

