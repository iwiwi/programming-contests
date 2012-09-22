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

int N, M;


int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    vector<int> cd(N + 1);
    for (int i = 1; i <= N; ++i) cd[i] = i;

    rep (i, M) {
      int x;
      scanf("%d", &x);
      int k = find(all(cd), x) - cd.begin();
      swap(cd[0], cd[k]);

    }

    for (int i = 1; i <= N; ++i) printf("%d\n", cd[i]);
  }

  return 0;
}

