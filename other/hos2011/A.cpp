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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;


const int MAX_N = 1000010;

int prime[MAX_N], prime_n;
bool is_composite[MAX_N + 1];

void sieve(int n) {
  is_composite[0] = is_composite[1] = true;
  for (int i = 2; i * i <= n; i++) {
    if (is_composite[i]) continue;
    for (int j = i; i * j <= n; j++) is_composite[i * j] = true;
  }
  prime_n = 0;
  for (int i = 2; i <= n; i++) {
    if (!is_composite[i]) prime[prime_n++] = i;
  }
}

typedef long long ll;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}





const ll MOD = 1000000009;

ll inv_prime[MAX_N];
map<int, int> pot, prv;
queue<int> que[80];

vector<int> ans;

void restore(ll x) {
  if (x == 1) return;

  ll p = prv[x];
  ans.pb(p);
  restore(x * inverse(p, MOD) % MOD);
}

bitset<MOD> bs;

int main() {
  const int M = 150;
  const int L = 75;
  sieve(M);
  rep (i, prime_n) inv_prime[i] = inverse(prime[i], MOD);

  pot[1] = 0;
  que[0].push(1);

  for (int c = 0; c < L; ++c) {
    while (!que[c].empty()) {
      ll x = que[c].front();
      que[c].pop();
      if (c > pot[x]) continue;

      rep (i, prime_n) {
        int p = prime[i];
        ll tc = c + p;
        if (tc > L) break;

        ll tx = x * p % MOD;
        if (pot.count(tx) == 0 || tc < pot[tx]) {
          pot[tx] = tc;
          prv[tx] = p;
          que[tc].push(tx);
        }
      }
    }
  }

  tr (pot, ite) bs.set(ite->first);

  ll X;
  while (cin >> X) {
    if (X == 1) {
      puts("1");
      puts("a");
      continue;
    }

    tr (pot, ite) {
      ll ax = ite->first;
      ll inv_ax = inverse(ax, MOD);

      rep (i, prime_n) {
        ll bx = prime[i];
        ll inv_bx = inv_prime[i];

        // ll cx = (X * inverse(ax * bx % MOD, MOD) % MOD + MOD) % MOD;
        ll cx = (X * inv_ax % MOD * inv_bx % MOD + MOD) % MOD;
        if (bs[cx] == 0) continue;

        int k = ite->second + bx + pot[cx];
        if (k <= M) {
          ans.clear();
          ans.pb(bx);
          restore(ax);
          restore(cx);

          string s(10, '#');
          rep (i, s.length()) s[i] = 'a' + i;

          vector<int> v = ans;
          cout << accumulate(all(v), 0) << endl;
          rep (i, v.size()) {
            rep (j, v[i]) cout << s << endl;
            next_permutation(all(s));
          }

          /*
          assert(accumulate(all(v), 0) <= 150);
          // rep (i, v.size()) printf("%d\n", v[i];)
          ll x = 1;
          rep (i, v.size()) x = (x * v[i]) % MOD;
          assert(x == X);
          // printf("%lld\n", x);
          */

          goto done;
        }
      }
    }
    puts("NO");
  done:;
  }


  return 0;
}

