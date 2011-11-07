#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <climits>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair
#define pb push_back

string A;
string B;

ll atoll(const string &s) {
  stringstream ss(s);
  ll r;
  ss >> r;
  return r;
}

string lltoa(ll x) {
  stringstream ss;
  ss << x;
  return ss.str();
}

ll position(int k, ll a) {
  ll ten = 1;
  ll res = 0;
  for (int i = 0; i <= k - 2; ++i) {
    res += 9 * (i + 1) * ten;
    ten *= 10;
  }
  res += (a - ten) * k;
  res += 1;
  return res;
}

ll small(const string &A) {
  string::size_type p = B.find(A);
  if (p != string::npos) {
    return p;
  }
  return -1;
}

ll solve(const string &A) {
  int L = A.length();
  if (A == "0") return 10;

  if (count(A.begin(), A.end(), '0') == L) {
    int k = L;
    ll res = 0, ten = 1;
    for (int i = 0; i <= k - 1; ++i) {
      res += 9 * (i + 1) * ten;
      ten *= 10;
    }
    res += 2;
    return res;
  }

  ll ans = 1E17;

  for (int k = 1; k <= min(16, L + 1); ++k) {
    rep (i, min(k, L)) {
      if (A[i] == '0') continue;  // Leading zero

      if (i + k <= L) {
        ll a = atoll(A.substr(i, k));

        string s, t;
        t = lltoa(a - 1);
        s += t.substr(t.length() - i);
        for (int j = 0; (int)s.length() < L; ++j) s += lltoa(a + j);
        s = s.substr(0, L);

        if (s != A) goto ng;
        ans = min(ans, position(k, a) - i);
      } else {
        string a = A.substr(i);
        string b = A.substr(0, i);
        int bl = b.length();
        b = lltoa(atoll(b) + 1);
        while (b.length() < bl) b = '0' + b;

        a.resize(k, 'X');
        rep (j, bl) {
          if (a[k - j - 1] == 'X') a[k - j - 1] = b[b.length() - j - 1];
          else if (a[k - j - 1] != b[b.length() - j - 1]) goto ng;
        }
        rep (j, k) if (a[j] == 'X') a[j] = '0';
        ll x = atoll(a);

        ans = min(ans, position(k, x) - i);
      }

   ng:;
    }
  }
  return ans;
}

int main() {
  stringstream ss;
  ss << 'X';  // padding
  for (int i = 1; i < 100000; ++i) ss << i;
  B = ss.str();

  while (false) {
    int l = 3 + rand() % 5;
    string s = "";
    rep (i, l) s += '0' + rand() % 10;
    cout << s << " " << small(s) << " " << solve(s) << endl;
    assert(small(s) == -1 || small(s) == solve(s));
  }

  for (;;) {
    cin >> A;
    if (A == "#") return 0;

    ll a = small(A);
    if (a == -1) a = solve(A);
    printf("%lld\n", a);
  }
}
