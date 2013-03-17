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
  int A[3], B[3];
  while (cin >> A[0] >> A[1] >> A[2]) {
    cin >> B[0] >> B[1] >> B[2];

    int ans = 0;
    sort(B, B + 3);
    do {
      ans = max(ans, (A[0] / B[0]) * (A[1] / B[1]) * (A[2] / B[2]));
    } while (next_permutation(B, B + 3));

    printf("%d\n", ans);
  }

  return 0;
}

