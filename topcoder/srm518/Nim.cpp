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
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

const int MAX_N = 1000010;

int prime[MAX_N], prime_n;
bool isn_prime[MAX_N + 1]; // false: 素数

void sieve(int n) {
  isn_prime[0] = isn_prime[1] = true;
  for (int i = 2; i * i <= n; i++) {
    if (isn_prime[i]) continue;
    for (int j = i; i * j <= n; j++) isn_prime[i * j] = true;
  }
  prime_n = 0;
  for (int i = 2; i <= n; i++) {
    if (!isn_prime[i]) prime[prime_n++] = i;
  }
}

typedef long long ll;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}

ll pow_mod(ll a, ll k, ll m) {
  if (k == 0) return 1;
  ll t = pow_mod(a, k / 2, m);
  return mod(mod(t * t, m) * (k % 2 ? a : 1), m);
}



typedef long long ll;
const ll MOD = 1000000007;

void fwt(vector<ll> &a) {
  int n = a.size();
  for (int k = n / 2; k >= 1; k /= 2) {
    for (int b = 0; b < n; b += k * 2) {
      for (int i = 0; i < k; ++i) {
        ll a1 = a[b + i], a2 = a[b + k + i];
        a[b + i] = (a1 + a2) % MOD;
        a[b + k + i] = (a1 - a2 + MOD) % MOD;
      }
    }
  }
}

void inv_fwt(vector<ll> &a) {
  fwt(a);
  ll t = pow_mod(inverse(2, MOD), __builtin_ctz(a.size()), MOD);
  rep (i, a.size()) a[i] = (a[i] * t) % MOD;
}

void pow(vector<ll> &a, ll k) {
  fwt(a);
  rep (i, a.size()) a[i] = pow_mod(a[i], k, MOD);
  inv_fwt(a);
}



struct Nim {
  int count(int K, int L) {
    sieve(L);

    vector<ll> A(65536, 0);
    rep (i, prime_n) A[prime[i]] = 1;

    pow(A, K);
    return A[0];
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 7; int Arg2 = 6; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 13; int Arg2 = 120; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 100; int Arg2 = 294844622; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 123456789; int Arg1 = 12345; int Arg2 = 235511047; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  Nim ___test;
  ___test.run_test(-1);
}
// END CUT HERE
