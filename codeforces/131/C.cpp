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

ll cmb[100][100];

int main() {
  cmb[0][0] = 1;
  for (int i = 1; i <= 40; ++i) {
    cmb[i][0] = 1;
    for (int j = 1; j <= i; ++j) cmb[i][j] = cmb[i-1][j-1] + cmb[i-1][j];
  }

  ll N, M, T;
  while (cin >> N >> M >> T) {
    ll ans = 0;
    for (int b = 4; b + 1 <= T; ++b) {
      ans += cmb[N][b] * cmb[M][T - b];
    }
    cout << ans << endl;
  }

  return 0;
}

