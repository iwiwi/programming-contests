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

string S;
map<pair<int, int>, ll> mem_len;

ll get_length(int l, int r) {
  if (mem_len.count(mp(l, r))) return mem_len[mp(l, r)];

  ll res = 0;
  for (int i = l; i < r; ++i) {
    if (isalpha(S[i])) {
      ++res;
    } else {
      assert(S[i] == '(');
      int lv = 1, j;
      for (j = i + 1; lv > 0; ++j) {
        if (S[j] == '(') ++lv;
        if (S[j] == ')') --lv;
      }
      int tl = i + 1, tr = j - 1;  // [tl, tr)
      ll n = 0;
      for (i = j; isdigit(S[i]); ++i) {
        n = n * 10 + (S[i] - '0');
      }
      ll ts = get_length(tl, tr);
      res += ts * n;
      --i;
    }
  }

  return mem_len[mp(l, r)] = res;
}

string extract(int l, int r, ll &b, ll &s) {
  string res = "";

  for (int i = l; i < r; ++i) {
    if (isalpha(S[i])) {
      if (b == 0) {
        res += S[i];
        --s;
      } else {
        --b;
      }
    } else {
      assert(S[i] == '(');
      int lv = 1, j;
      for (j = i + 1; lv > 0; ++j) {
        if (S[j] == '(') ++lv;
        if (S[j] == ')') --lv;
      }
      int tl = i + 1, tr = j - 1;  // [tl, tr)
      ll n = 0;
      for (i = j; isdigit(S[i]); ++i) {
        n = n * 10 + (S[i] - '0');
      }
      ll ts = get_length(tl, tr);

      if (b >= ts * n) {
        b -= ts * n;
      } else {
        ll k = b / ts;
        b -= ts * k;
        n -= k;
        if (b + s <= ts) {
          res += extract(tl, tr, b, s);
          break;
        } else {
          ll tb = 0;
          string t1 = extract(tl, tr, tb, ts), t2 = "";
          rep (i, n) {
            t2 += t1;
            if ((ll)t2.length() >= b + s) break;
          }
          t2 = t2.substr(b, min(s, (ll)t2.length() - b));
          res += t2;
          b = 0;
          s -= t2.length();
        }
      }
      --i;
    }

    if (s == 0) break;
  }

  return res;
}

int main() {
  ll B, L, N;
  while (cin >> B >> L >> N >> S) {
    N = S.length();
    mem_len.clear();

    if (B < 0) {
      ll len = get_length(0, N);
      B += len;
    }

    ll tb = B, ts = L;
    string ans = extract(0, N, tb, ts);
    assert((ll)ans.length() == L);
    cout << ans << endl;
  }

  return 0;
}

