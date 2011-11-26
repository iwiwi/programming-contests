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
  for (;;) {
    int M, N;
    cin >> M >> N;
    if (M == 0 && N == 0) return 0;

    vector<int> res(M);
    rep (i, M) res[i] = i;
    int k = 0;

    for (int j = 1; j <= N; ++j) {
      string ans;

      if (j % 3 == 0 && j % 5 == 0) ans = "FizzBuzz";
      else if (j % 3 == 0) ans = "Fizz";
      else if (j % 5 == 0) ans = "Buzz";
      else {
        char buf[256];
        sprintf(buf, "%d", j);
        ans = string(buf);
      }

      string s;
      cin >> s;

      if (res.size() == 1) continue;

      if (s == ans) {
        k = (k + 1) % res.size();
      }
      else {
        res.erase(res.begin() + k);
        k %= res.size();
      }
    }

    bool first = true;
    rep (i, res.size()) {
      if (first) first = false;
      else putchar(' ');
      printf("%d", res[i] + 1);
    }
    puts("");
  }

  return 0;
}

