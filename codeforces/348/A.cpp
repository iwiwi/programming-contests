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

typedef long long ll;

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);

    ll lb = 0, ub = 1LL << 40;
    while (ub - lb > 1) {
      ll X = (lb + ub) / 2;

      ll t = 0;
      rep (i, N) {
        if (A[i] > X) goto dmp;
        t += X - A[i];
      }
      if (t < X) goto dmp;

      ub = X;
      continue;
   dmp:
      lb = X;
    }

    cout << ub << endl;
  }

  return 0;
}
