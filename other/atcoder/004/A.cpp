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

#include <complex>
typedef complex<double> p_t;

int main() {
  int N;
  scanf("%d", &N);

  double X[110], Y[110];
  rep (i, N) scanf("%lf%lf", X + i, Y + i);

  double ans = 0.0;
  rep (i, N) rep (j, i) ans = max(ans, hypot(X[i] - X[j], Y[i] - Y[j]));
  printf("%.10f\n", ans);

  return 0;
}

