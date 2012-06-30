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
  while (cin >> N) {
    vector<string> W(N);
    rep (i, N) cin >> W[i];
    W.back() = W.back().substr(0, W.back().length() - 1);

    int ans =
        count(all(W), "TAKAHASHIKUN") +
        count(all(W), "Takahashikun") +
        count(all(W), "takahashikun");

    printf("%d\n", ans);
  }

  return 0;
}

