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

int N, K;
int A[100010];

int main() {
  scanf("%d%d", &N, &K);
  rep (i, N) scanf("%d", &A[i]);

  map<int, int> cnt;
  set<int> crr;
  rep (i, N) {
    if (++cnt[A[i]] == 1) crr.insert(A[i]);
    else crr.erase(A[i]);

    if (i >= K) {
      int c = --cnt[A[i- K]];
      if (c == 1) crr.insert(A[i - K]);
      else if (c == 0) crr.erase(A[i - K]);
    }

    if (i >= K - 1) {
      if (crr.empty()) puts("Nothing");
      else {
        iter(crr) ite = crr.end();
        --ite;
        printf("%d\n", *ite);
      }
    }
  }

  return 0;
}

