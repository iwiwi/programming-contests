#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <set>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)

typedef complex<double> c_t;

int main() {
  int N, M;
  while (2 == scanf("%d%d", &N, &M)) {
    vector<pair<int, int> > A(N);
    rep (i, N) scanf("%d%d", &A[i].second, &A[i].first);

    multiset<int> B;
    rep (i, M) {
      int w;
      scanf("%d", &w);
      B.insert(w);
    }

    int ans = 0;
    sort(A.begin(), A.end());
    rep (i, N) {
      int mi = A[i].second, ma = A[i].first;

      multiset<int>::iterator ite = B.lower_bound(mi);
      if (ite == B.end()) continue;
      if (*ite > ma) continue;
      ++ans;
      B.erase(ite);
    }
    printf("%d\n", ans);
  }
}
