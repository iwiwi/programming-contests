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
  int N;
  string S;
  while (cin >> N >> S) {
    int i = 0, ans = 0;
    while (i < N - 1) {
      for (int j = 1; j <= 3; ++j) {
        if (S[i + j] == '.') {
          i += j;
          goto done;
        }
      }
      // oops...
      ++ans;
      i += 3;
   done:;
    }
    printf("%d\n", ans);
  }
  return 0;
}

