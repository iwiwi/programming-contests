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
int N;
ll L, T;

int A[2000010];

int main() {
  int l_, t_;
  while (3 == scanf("%d%d%d", &N, &l_, &t_)) {
    L = l_;
    T = t_;

    rep (i, N) {
      scanf("%d", &A[i]);
      A[N + i] = A[i] + L;
    }

    ll X = 2 * T;
    ll Y = X % L;
    double always = double(N - 1) * (X / L);

    double ans1 = 0;
    double ans2 = 0;

    int j = 0;
    rep (i, N) {
      while (j < i + N && A[j] - A[i] <= Y) ++j;
      // printf("[%d, %d)\n", i, j);
      ans1 += j - i - 1;
      ans2 += always;
    }

    printf("%.10f\n", (ans1 + ans2) / 4.0);
  }

  return 0;
}

