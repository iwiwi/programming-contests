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

int A[100010];
bool rev[100010];
char ans[100010];

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    rep (i, N) scanf("%d", &A[i]);

    memset(rev, 0, sizeof(rev));
    int x = A[N - 1];
    for (int i = N - 2; i >= 0; --i) {
      int a = A[i];
      if (a >= x) {
        // +a -x
        // printf("%d: +\n", i);
        x = +a -x;
        rev[i + 1] ^= true;
      } else {
        // -a +x
        // printf("%d: -\n", i);
        x = -a +x;
        rev[i] ^= true;
        rev[i + 1] ^= true;
      }
      assert(0 <= x && x <= A[i]);
    }

    bool p = true;
    rep (i, N) {
      p ^= rev[i];
      ans[i] = p ? '+' : '-';
    }
    ans[N] = '\0';
    puts(ans);
  }

  return 0;
}

