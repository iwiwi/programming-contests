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
  string line;
  while (getline(cin, line)) {
    int N = atoi(line.c_str());

    string S;
    getline(cin, S);

    vector<int> sens;
    int j = 0;
    for (int i = 0; i < (int)S.length(); ++i) {
      char c = S[i];
      if (c == '.' || c == '?' || c == '!') {
        ++i;
        sens.pb(i - j);
        j = i + 1;
      }
    }

    // rep (i, sens.size()) printf("%d\n", sens[i]);

    int ans = 0, crr = 0;
    rep (i, sens.size()) {
      if (sens[i] > N) goto ng;
      int tmp = crr == 0 ? sens[i] : crr + 1 + sens[i];

      if (tmp <= N) {
        crr = tmp;
      }
      else {
        ++ans;
        crr = sens[i];
      }
    }
    if (crr > 0) ++ans;
    printf("%d\n", ans);
    continue;
   ng:;
    puts("Impossible");
  }

  return 0;
}

