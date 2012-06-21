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
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)


int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    double D[510];
    rep (i, N) scanf("%lf", &D[i]);

    double S = accumulate(D, D + N, 0.0);
    printf("%.f\n", S);

    double ma = *max_element(D, D + N);
    double re = S - ma;
    if (ma < re) puts("0");
    else printf("%.f\n", ma - re);

    break;
  }

  return 0;
}

