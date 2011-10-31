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

int N, M;

int solve(int x) {
  int h = max(0, N - x - x);
  int w = max(0, M - x - x);
  return (h * w + 1) / 2;
}

int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    int X;
    scanf("%d", &X);
    printf("%d\n", solve(X - 1) - solve(X));
  }

  return 0;
}

