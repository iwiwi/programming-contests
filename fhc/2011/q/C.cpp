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
#include <numeric>
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
  cin >> N;
  rep (ca, N) {
    int M;
    cin >> M;

    vector<string> A(M);
    rep (i, M) cin >> A[i];
    sort(all(A));

    string ans = accumulate(all(A), string(""));
    do {
      string tmp = accumulate(all(A), string(""));
      ans = min(ans, tmp);
    } while (next_permutation(all(A)));

    cout << ans << endl;
  }

  return 0;
}

