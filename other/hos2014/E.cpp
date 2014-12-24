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
#define eb(e) emplace_back(e)
#define mp(a, b) make_pair(a, b)


int main() {
  int T;
  scanf("%d", &T);

  rep (t, T) {
    int N, M;
    scanf("%d%d", &N, &M);

    vector<int> A(N, N - 1);
    rep (i, M) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      --A[a];
      --A[b];
    }

    printf("%d\n", *min_element(all(A)) - 1);
  }
}
