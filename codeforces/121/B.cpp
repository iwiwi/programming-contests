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
  int N, K;
  while (cin >> N >> K) {
    string D;
    cin >> D;

    int p = 0;
    while (K > 0) {
      for (; p + 1 < N; ++p) {
        if (D[p] == '4' && D[p + 1] == '7') {
          break;
        }
      }
      if (p + 1 == N) break;

      if (p % 2 == 1) {
        if (p > 0 && D[p - 1] == '4') {
          K %= 2;
          if (K == 0) break;
        }
        D[p] = '7';
      } else {
        D[p + 1] = '4';
      }
      --K;
      p = max(0, p - 1);
    }

    cout << D << endl;
  }

  return 0;
}

