#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back

typedef long long ll;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
  int N;
  while (cin >> N && N != 0) {
    vector<ll> gu, ki;
    int M = N * (N + 1) / 2;
    rep (i, M) {
      ll t;
      cin >> t;
      if (t % 2 == 0) gu.pb(t);
      else ki.pb(t);
    }
    sort(gu.begin(), gu.end());
    sort(ki.begin(), ki.end());

    // A_0
    ll a0 = 0;

    ll m01 = gu[0];
    ll m02 = gu[1];
    ll m12 = ki[0];
    // cout << m01 << " " << m02 << " " << m12 << endl;

    ll g = gcd(m01, m12);
    m01 /= g;
    m12 /= g;
    m02 /= m12;
    a0 = round(sqrt(m01 * m02));

    cout << a0 << endl;

    // A_i (i > 0)
    vector<ll> ans;
    rep (i, gu.size()) {
      if (i) cout << " ";
      cout << gu[i] / a0;
    }
    cout << endl;
  }
}
