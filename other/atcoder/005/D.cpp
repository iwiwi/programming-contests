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

const int K = 30;
const int INF = 9876543;

string P;
int L;
ll A[110];

map<int, vector<int> > can[110];
map<int, pair<int, vector<ll> > > mem[110][110];

pair<int, vector<ll> > search(int k, int p, int c) {
  if (c == A[p]) return mp(0,   vector<ll>(k, 0));
  if (c  > A[p]) return mp(INF, vector<ll>(k, 0));

  if (k == 0) {
    if (c == A[p]) return mp(0  , vector<ll>());
    else        return mp(INF, vector<ll>());
  } else {
    if (mem[k][p].count(c)) return mem[k][p][c];

    pair<int, vector<ll> > res = search(k - 1, p, c);
    res.second.pb(0);
    assert((int)res.second.size() == k);

    for (int a = 0; a <= 9 * k; ++a) {
      if (A[p] % 10 != (c + a) % 10) continue;
      if (!can[k].count(a)) continue;

      pair<int, vector<ll> > t = search(k, p + 1, (c + a) / 10);
      t.first += k;

      if (t.first < res.first) {
        res = t;
        const vector<int> &s = can[k][a];
        rep (i, k) res.second[i] = res.second[i] * 10 + s[i];
      }
    }

    return mem[k][p][c] = res;
  }
}

int main() {
  string bs;
  while (cin >> bs) {
    cin >> P;
    L = P.length();

    rep (i, L) if (!cpresent(bs, P[i])) goto no;
    cout << P << endl;
    continue;
 no:
    L += 5;
    A[0] = atoll(P.c_str());
    for (int i = 1; i < L; ++i) A[i] = A[i - 1] / 10;

    vector<int> B(bs.length());
    rep (i, bs.length()) B[i] = bs[i] - '0';
    can[0][0] = vector<int>();

    rep (i, K) {
      can[i + 1].clear();
      tr (can[i], ite) rep (j, B.size()) (can[i + 1][ite->first + B[j]] = ite->second).push_back(B[j]);
    }

    for (int k = 0; k <= K; ++k) for (int p = 0; p <= L; ++p) mem[k][p].clear();

    pair<int, vector<ll> > ans = mp(INF, vector<ll>());
    for (int k = 1; k <= K; ++k) {
      pair<int, vector<ll> > t = search(k, 0, 0);
      t.first += k;
      // rep (i, t.second.size()) printf("%lld ", t.second[i]); puts("");
      ans = min(ans, t);
    }

    vector<ll> t = ans.second;
    rep (i, t.size()) printf("%lld%c", t[i], i + 1 == (int)t.size() ? '=' : '+');
    puts("");
  }

  return 0;
}

