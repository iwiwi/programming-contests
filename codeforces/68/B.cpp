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
  int N, K;
  while (2 == scanf("%d%d", &N, &K)) {
    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);

    double lb = 0.0, ub = 1000;
    rep (iter, 100) {
      double tmp = (lb + ub) / 2.0;

      double req = 0.0;
      rep (i, N) {
        if (A[i] > tmp) req -= (A[i] - tmp) * (100.0 - K) / 100.0;
        else req += tmp - A[i];
      }

      if (req > 0.0) ub = tmp;
      else lb = tmp;
    }

    printf("%.10f\n", lb);
  }

  return 0;
}

