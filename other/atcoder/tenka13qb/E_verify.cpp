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

#include <complex>
typedef complex<double> p_t;

int N;
p_t P[110];

double takuya() {
  bool usd[110] = {};
  int c = 0;
  double ans = 0;

  for (;;) {
    printf("takuya: %d\n", c);
    usd[c] = true;

    vector<pair<int, int> > dks;
    rep (tk, N) if (!usd[tk]) {
      dks.pb(mp(norm(P[c] - P[tk]), tk));
    }

    sort(all(dks));

    int tc;
    if (dks.empty()) return ans;
    else tc = dks[0].second;
    ans += abs(P[c] - P[tc]);
    c = tc;
  }
}

double takahashi() {
  bool usd[110] = {};
  int c = 0;
  double ans = 0;

  for (;;) {
    printf("takahashi: %d\n", c);
    usd[c] = true;

    vector<pair<int, int> > dks;
    rep (tk, N) if (!usd[tk]) {
      dks.pb(mp(norm(P[c] - P[tk]), tk));
    }

    sort(all(dks));

    int tc;
    if (dks.empty()) return ans;
    else if (dks.size() <= 2) tc = dks[0].second;
    else tc = dks[1].second;
    ans += abs(P[c] - P[tc]);
    c = tc;
  }
}

int main() {
  scanf("%d", &N);
  rep (i, N) scanf("%lf%lf", &P[i].real(), &P[i].imag());
  printf("%f\n", takuya());
  printf("%f\n", takahashi());
  return 0;
}

