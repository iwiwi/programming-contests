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
  int lb = 1, ub = 1000000001;  // [lb, ub)
  while (ub - lb > 1) {
    int x = (lb + ub) / 2;
    printf("?%d\n", x); fflush(stdout);

    int r;
    scanf("%d", &r);
    if (r == 0) {
      printf("!%d\n", x);
      return 0;
    }

    if (r == 1) lb = x + 1;
    else ub = x;
  }
  printf("!%d\n", lb);
  return 0;
}

