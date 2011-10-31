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

int A[5];

int read() {
  char buf[256];
  scanf("%s", buf);
  if (buf[0] == 'S') return 0;
  else if (buf[0] == 'M') return 1;
  else if (buf[0] == 'L') return 2;
  else if (buf[1] == 'L') return 3;
  else return 4;
}

int main() {
  rep (i, 5) scanf("%d", A + i);
  int K;
  scanf("%d", &K);
  rep (i, K) {
    int t = read();
    for (int d = 0; ; ++d) {
      for (int s = 1; s >= -1; s -= 2) {
        int x = t + d * s;
        if (0 <= x && x < 5 && A[x] > 0) {
          --A[x];
          if (x == 0) puts("S");
          else if (x == 1) puts("M");
          else if (x == 2) puts("L");
          else if (x == 3) puts("XL");
          else puts("XXL");
          goto done;
        }
      }
    }
  done:;
  }

  return 0;
}

