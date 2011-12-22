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

typedef long long ll;

const ll MOD = 1000003;

typedef long long ll;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}



typedef vector<ll> poly_t;

// a(x)
ll calc(const poly_t &a, ll x) {
  ll t = 1, s = 0;
  rep (i, a.size()) {
    s = (s + t * a[i]) % MOD;
    t = (t * x) % MOD;
  }
  return (s + MOD) % MOD;
}

// t * a
poly_t scalar(poly_t a, ll t) {
  rep (i, a.size()) a[i] = (a[i] * t) % MOD;
  return a;
}

// a + b
poly_t add(poly_t a, poly_t b) {
  if (a.size() < b.size()) a.swap(b);
  rep (i, b.size()) a[i] = (a[i] + b[i]) % MOD;
  return a;
}

// a * b
poly_t mul(const poly_t &a, const poly_t &b) {
  if (a.empty() && b.empty()) return poly_t();
  poly_t r(a.size() + b.size() - 1);
  rep (i, a.size()) rep (j, b.size()) r[i + j] = (r[i + j] + a[i] * b[j]) % MOD;
  return r;
}

// b_0 * a^0 + b_1 * a^1 + b_2 * a^2 + ...
poly_t compose(const poly_t &a, const poly_t &b) {
  poly_t r, x(1, 1);
  rep (i, b.size()) {
    r = add(r, scalar(x, b[i]));
    x = mul(x, a);
  }
  return r;
}



const int MAX_K = 2500;

poly_t sum_coef[MAX_K + 10];

void init_sum(int K) {
  static ll inv[MAX_K + 10];
  for (int i = 1; i <= K + 1; ++i) inv[i] = inverse(i, MOD);

  sum_coef[0] = poly_t(2); sum_coef[0][0] = sum_coef[0][1] = 1;
  sum_coef[1] = poly_t(3); sum_coef[1][1] = sum_coef[1][2] = inv[2];

  for (int i = 2; i <= K; ++i) {
    sum_coef[i] = poly_t(i + 2);
    for (int j = i; j > 0; --j) {
      sum_coef[i][j + 1] = sum_coef[i - 1][j] * inv[j + 1] % MOD * i % MOD;
    }
    sum_coef[i][1] = 0;
    sum_coef[i][1] = (1 - calc(sum_coef[i], 1) + MOD) % MOD;
  }
}

// a(0) + a(1) + ... + a(x)
poly_t sum(const poly_t &a) {
  poly_t r;
  rep (i, a.size()) r = add(r, scalar(sum_coef[i], a[i]));
  return r;
}


struct P8XCoinChange {
  int solve(long long coins_sum, vector<long long> values) {
    int N = values.size();
    vector<ll> C(N - 1);
    rep (i, N - 1) C[i] = values[i + 1] / values[i];

    vector<ll> M(N);
    for (int i = N - 1; i >= 0; --i) {
      M[i] = coins_sum / values[i];
      coins_sum %= values[i];
    }

    init_sum(N + 10);

    poly_t dp[60];
    dp[0] = poly_t(1, 1);

    for (int i = 1; i < N; ++i) {
      poly_t t(2);
      t[0] = 0;
      t[1] = values[i] / values[i - 1] % MOD;

      poly_t s(2);
      s[0] = M[i] % MOD;
      s[1] = 1;
      dp[i] = compose(s, sum(compose(t, dp[i - 1])));
    }

    return (calc(dp[N - 1], 0) + MOD) % MOD;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 4LL; long Arr1[] = {1, 3}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 4LL; long Arr1[] = {1, 2, 4}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, solve(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 3LL; long Arr1[] = {1, 5}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, solve(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 11LL; long Arr1[] = {1, 2, 6}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(3, Arg2, solve(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 1000000000000000000LL; long Arr1[] = {1, 1000000000, 1000000000000000000}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 997005; verify_case(4, Arg2, solve(Arg0, Arg1)); }
	void test_case_5() { long long Arg0 = 961320341778342848LL; long Arr1[] = {1,2,10,30,150,300,1200,2400,4800,14400,
28800,57600,288000,576000,2304000,9216000,
18432000,73728000,221184000,663552000,
1327104000,5308416000,31850496000,
95551488000,191102976000,764411904000,
1528823808000,6115295232000,18345885696000,
36691771392000,73383542784000,220150628352000,
440301256704000,1320903770112000,3962711310336000,
15850845241344000,31701690482688000,95105071448064000,
475525357240320000,951050714480640000}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 245264; verify_case(5, Arg2, solve(Arg0, Arg1)); }
	void test_case_6() { long long Arg0 = 1000000000000000000LL; long Arr1[] = {1, 2}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 499989; verify_case(6, Arg2, solve(Arg0, Arg1)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  P8XCoinChange ___test;
  ___test.run_test(-1);
}
// END CUT HERE
