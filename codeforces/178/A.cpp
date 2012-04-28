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

typedef long long ll;

int N;
ll A[1000010];

int main() {
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);

  while (cin >> N) {
    rep (i, N) cin >> A[i];

    ll ans = 0;
    rep (i, N - 1) {
      int t = 1;
      while (i + t * 2 < N) t *= 2;
      ans += A[i];
      cout << ans << endl;
      A[i + t] += A[i];
    }
  }

  return 0;
}

