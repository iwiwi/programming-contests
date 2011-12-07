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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

const int L = 10000000;


struct rmq {
  int n;
  int dat[2000010];

  void init(int n_) {
    for (n = 1; n < n_; n *= 2);
    fill(dat, dat + 2 * n, INT_MIN);
  }

  void update(int k, int a) {
    dat[n + k] = a;
    for (int i = (n + k) / 2; i > 0; i /= 2) {
      dat[i] = max(dat[i * 2], dat[i * 2 + 1]);
    }
  }

  int query(int a, int b) {
    int ret = INT_MIN;
    for (; 0 < a && a + (a & -a) <= b; a += a & -a) {
      int i = (n + a) / (a & -a);
      ret = max(ret, dat[i]);
    }
    for (; a < b; b -= b & -b) {
      int i = (n + b) / (b & -b) - 1;
      ret = max(ret, dat[i]);
    }
    return ret;
  }
};


const int MAX_N = 1000010;

int prime[MAX_N], prime_n;
bool composite[MAX_N + 1]; // false: 素数

void sieve(int n) {
  composite[0] = composite[1] = true;
  for (int i = 2; i * i <= n; i++) {
    if (composite[i]) continue;
    for (int j = i; i * j <= n; j++) composite[i * j] = true;
  }
  prime_n = 0;
  for (int i = 2; i <= n; i++) {
    if (!composite[i]) prime[prime_n++] = i;
  }
}


rmq me, da;

int advance(int q, int N) {
  int t;
  if (q == INT_MIN) t = L - 0;  // lose
  else if (q <= N) t = L - (q + 1);  // lose
  else t = (L - q) + 1;  // win

  return t;
}

struct PrimeCompositeGame {
  int theOutcome(int N, int K) {
    if (N == 1) return 0;
    sieve(N);
    me.init(N + 10);
    da.init(N + 10);

    int ans = INT_MIN;

    for (int i = 2; i <= N; ++i) {
      { // me
        int q = da.query(max(0, i - K), i);
        int t = advance(q, N);
        if (composite[i]) me.update(i, t);

        if (i == N) ans = t;
      }
      { // da
        int q = me.query(max(0, i - K), i);
        int t = advance(q, N);
        if (!composite[i]) da.update(i, t);
      }
    }

    if (ans <= N) return ans;
    else return -(L - ans);
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 1; verify_case(0, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 58; int Arg1 = 1; int Arg2 = 0; verify_case(1, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 30; int Arg1 = 3; int Arg2 = -2; verify_case(2, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 3; int Arg2 = 1; verify_case(3, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 526; int Arg1 = 58; int Arg2 = 19; verify_case(4, Arg2, theOutcome(Arg0, Arg1)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  PrimeCompositeGame ___test;
  ___test.run_test(-1);

  for (;;) {
    int n = 1 + rand() % 474747;
    int k = 1 + rand() % n;
    ___test.theOutcome(n, k);
  }

}
// END CUT HERE
