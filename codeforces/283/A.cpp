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

double add[200010];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    vector<int> A(1, 0);
    double sum_num = 0, sum_add = 0;
    memset(add, 0, sizeof(add));

    rep (q, N) {
      int t;
      scanf("%d", &t);
      if (t == 1) {
        int a, x;
        scanf("%d%d", &a, &x);
        sum_add += a * (double)x;
        add[a] += x;
      } else if (t == 2) {
        int x;
        scanf("%d", &x);
        A.pb(x);
        sum_num += x;
      } else if (t == 3) {
        sum_num -= A.back();
        int n = A.size();
        A.pop_back();

        sum_add -= add[n];
        add[n - 1] += add[n];
        add[n] = 0;
      }

      printf("%.10f\n", (sum_num + sum_add) / A.size());
    }
  }

  return 0;
}

