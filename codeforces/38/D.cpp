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
int X1[110], X2[110];
int Y1[110], Y2[110];

const double EPS = 1E-10;

int solve(int *x1, int *x2) {
  for (int i = 1; i < N; ++i) {
    // double x = (x1[i] + x2[i]) / 2.0;
    // if (x < x1[i - 1] || x2[i - 1] < x) return i;

    double cx = 0.0;
    double cw = 0.0;
    for (int j = i; j >= 1; --j) {
      double x = (x1[j] + x2[j]) / 2.0;
      double w = pow(x2[j] - x1[j], 3.0);
      cx = (cx * cw + x * w) / (cw + w);
      cw = cw + w;

      if (cx < x1[j - 1] - EPS || x2[j - 1] + EPS < cx) return i;
    }
  }
  return N;
}

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) {
      scanf("%d%d%d%d", X1 + i, Y1 + i, X2 + i, Y2 + i);
      if (X1[i] > X2[i]) swap(X1[i], X2[i]);
      if (Y1[i] > Y2[i]) swap(Y1[i], Y2[i]);
    }
    printf("%d\n", min(solve(X1, X2), solve(Y1, Y2)));
  }
  
  return 0;
}

