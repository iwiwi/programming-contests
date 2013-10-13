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

const int K = 2000000;

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    vector<bool> dmp(K + 1);

    for (int p = 2; p * p <= K; ++p) {
      if (dmp[p]) continue;
      for (int q = p * p; q <= K; q += p) dmp[q] = true;
    }

    vector<int> ps;
    for (int p = 2; p <= K; ++p) if (!dmp[p]) ps.pb(p);
    assert((int)ps.size() >= N);

    rep (i, N) printf("%d%c", ps[i], i + 1 == N ? '\n' : ' ');
  }
}
