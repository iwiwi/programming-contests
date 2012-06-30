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
  // rep (i, 10) printf("? %.12f\n", 0.0);

  printf("? %.12f\n", 0.0);
  printf("? %.12f\n", sqrt(2.0));
  printf("? %.12f\n", sqrt(2.0) * 2.0);
  fflush(stdout);

  double h, y1, y2;
  scanf("%lf%lf%lf", &h, &y1, &y2);

  y1 -= h;
  y2 -= h;

  double v = (y1 * 4 - y2) / 2.0;
  double g = -y1 + v;

  printf("! %.12f %.12f %.12f\n", h, v, g);

  // puts("HELLO!");

  return 0;
}

