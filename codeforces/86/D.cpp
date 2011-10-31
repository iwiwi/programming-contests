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

typedef long long ll;

vector<int> order(const vector<pair<int, int> > &itvs) {
  static const int B = 500;  // = sqrt MAX_N
  int K = itvs.size();
  vector<pair<pair<int, int>, int> > vs(K);
  rep (i, K) vs[i] = mp(mp(itvs[i].first / B, itvs[i].second), i);
  sort(all(vs));
  vector<int> res(K);
  rep (i, K) res[i] = vs[i].second;
  return res;
}

ll ans[200010];

int N, M;
int A[200010];
int cnt[1000010];

void process(const vector<pair<int, int> > &itvs) {
  vector<int> ord = order(itvs);

  ll crr = 0;
  int l = 0, r = 0;  // [l, r)
  rep (i, itvs.size()) {
    pair<int, int> itv = itvs[ord[i]];
    for (; l < itv.first; ++l) {
      // position |l| comes in
      --cnt[A[l]];
      crr -= ll(A[l]) * (cnt[A[l]] * 2 + 1);
    }
    while (itv.first < l) {
      --l;
      // position |l| goes out
      crr += ll(A[l]) * (cnt[A[l]] * 2 + 1);
      ++cnt[A[l]];
    }
    for (; r < itv.second; ++r) {
      // position |r| comes in
      crr += ll(A[r]) * (cnt[A[r]] * 2 + 1);
      ++cnt[A[r]];
    }
    while (itv.second < r) {
      --r;
      // position |r| goes out
      --cnt[A[r]];
      crr -= ll(A[r]) * (cnt[A[r]] * 2 + 1);
    }
    ans[ord[i]] = crr;
  }
}

int main() {
  scanf("%d%d", &N, &M);
  rep (i, N) scanf("%d", &A[i]);

  vector<pair<int, int> > itvs(M);
  rep (i, M) {
    scanf("%d%d", &itvs[i].first, &itvs[i].second);
    --itvs[i].first;
  }

  process(itvs);

  rep (i, M) cout << ans[i] << endl;

  return 0;
}

