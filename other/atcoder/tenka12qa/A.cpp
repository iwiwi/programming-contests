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

int main() {
  int N;
  while (cin >> N) {
    ll a[110] = {}, t = 1;
    a[0] = 1;
    for (int i = 1; i <= N; ++i) {
      ll s = 0;
      for (int j = 0; j < i - 1; ++j) s += a[j];
      a[i] = s;
      t += s;
    }
    cout << t << endl;
  }

  return 0;
}

