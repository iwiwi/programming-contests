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
  string A, B;
  while (cin >> A >> B) {
    int L = A.length();

    int c47 = 0, c74 = 0;
    rep (i, L) {
      if (A[i] == '4' && B[i] == '7') ++c47;
      if (A[i] == '7' && B[i] == '4') ++c74;
    }

    printf("%d\n", max(c74, c47));
  }

  return 0;
}

