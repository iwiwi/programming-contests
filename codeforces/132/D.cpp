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


char A[1000010];

int main() {
  while (1 == scanf("%s", A)) {
    int N = strlen(A);
    reverse(A, A + N);

    vector<pair<int, char> > res;
    for (int i = 0; i < N; ++i) {
      if (A[i] == '0') continue;

      if (A[i] == '1') {
        int j = i + 1;
        while (A[j] == '1' || (A[j] == '0' && A[j + 1] == '1')) ++j;
        int n = j - i, z = count(A + i, A + j, '0');
        if (n - z < 2 + z) {
          for (int k = i; k < j; ++k) if (A[k] == '1') res.pb(mp(k, '+'));
        } else {
          res.pb(mp(i, '-'));
          for (int k = i; k < j; ++k) if (A[k] == '0') res.pb(mp(k, '-'));
          res.pb(mp(j, '+'));
        }
        i = j;
      }
    }

    printf("%d\n", (int)res.size());
    rep (i, res.size()) printf("%c2^%d\n", res[i].second, res[i].first);
  }

  return 0;
}

