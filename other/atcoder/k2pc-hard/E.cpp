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

ll A[100010], P;
vector<ll> po[1000010];
int ans[100010];
int cnt[1000010];

vector<int> order(const vector<pair<int, int> > &itvs) {
  static const int B = 500;
  int K = itvs.size();
  vector<pair<pair<int, int>, int> > vs(K);
  rep (i, K) vs[i] = mp(mp(itvs[i].first / B, itvs[i].second), i);
  sort(all(vs));
  vector<int> res(K);
  rep (i, K) res[i] = vs[i].second;
  return res;
}

void process(const vector<pair<int, int> > &itvs) {
  vector<int> ord = order(itvs);
  int l = 0, r = 0;  // [l, r)
  ll v = 0;
  rep (i, itvs.size()) {
    pair<int, int> itv = itvs[ord[i]];
    while (itv.first < l) {
      --l;
      // position |l| comes in
      (v += po[A[l]][++cnt[A[l]]]) %= P;
    }
    for (; r < itv.second; ++r) {
      // position |r| comes in
      (v += po[A[r]][++cnt[A[r]]]) %= P;
    }
    for (; l < itv.first; ++l) {
      // position |l| goes out
      (v -= po[A[l]][cnt[A[l]]--]) %= P;
    }
    while (itv.second < r) {
      --r;
      // position |r| goes out
      (v -= po[A[r]][cnt[A[r]]--]) %= P;
    }
    ans[ord[i]] = (v + P) % P;
  }
}

void naive(vector<pair<int, int> > itvs) {
  rep (x, itvs.size()) {
    int s = itvs[x].first;
    int t = itvs[x].second;

    ll val = 0;
    for (int i = s; i < t; ++i) {
      int c = 0, a = A[i];
      for (int j = s; j <= i; ++j) if (A[j] == a) ++c;
      (val += po[a][c]) %= P;
    }
    printf("[%d, %d): %lld (vs. %d)\n", s, t, val, ans[x]);
    assert(val == ans[x]);
  }
  puts("PASSED SYSTEM TEST");
}



int main() {
  int N, Q;
  while (3 == scanf("%d%d%lld", &N, &Q, &P)) {
    rep (i, N) {
      ll a;
      scanf("%lld", &a);

      A[i] = a;
      if (po[a].empty()) po[a].pb(1);
      po[a].pb(po[a].back() * a % P);
    }

    vector<pair<int, int> > itvs(Q);
    rep (i, Q) {
      scanf("%d%d", &itvs[i].first, &itvs[i].second);
      --itvs[i].first;
    }

    memset(cnt, 0, sizeof(cnt));
    process(itvs);
    rep (i, Q) printf("%d\n", ans[i]);

    // naive(itvs);
  }

  return 0;
}

