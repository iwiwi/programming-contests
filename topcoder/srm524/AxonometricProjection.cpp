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

const ll MOD = 1000000009;

ll cmb[1010][1010];

void init_cmb(int N) {
  cmb[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    cmb[i][0] = 1;
    for (int j = 1; j <= i; ++j) cmb[i][j] = (cmb[i-1][j-1] + cmb[i-1][j]) % MOD;
  }
}

struct AxonometricProjection {
  int howManyWays(vector <int> A, vector <int> B) {
    init_cmb(60);

    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());

    vector<int> hs(A.begin(), A.end());
    hs.insert(hs.end(), B.begin(), B.end());
    sort(hs.rbegin(), hs.rend());
    hs.erase(unique(hs.begin(), hs.end()), hs.end());

    ll ans = 1;
    rep (i, hs.size()) {
      int h = hs[i];

      int a0 = 0, a1 = 0, b0 = 0, b1 = 0;
      rep (i, A.size()) {
        if (A[i] == h) ++a0;
        if (A[i] > h) ++a1;
      }
      rep (i, B.size()) {
        if (B[i] == h) ++b0;
        if (B[i] > h) ++b1;
      }

      ll tmp = 0;
      for (int al = 0; al <= a0; ++al) {
        for (int bl = 0; bl <= b0; ++bl) {
          ll t = 1;
          if ((al + bl) % 2) t *= -1;
          t = t * cmb[a0][al] % MOD;
          t = t * cmb[b0][bl] % MOD;

          int ah = a0 - al, bh = b0 - bl;
          int ch = ah * bh + ah * b1 + a1 * bh;
          int cl = al * bl + al * (bh + b1) + (ah + a1) * bl;

          rep (i, cl) t = t * h % MOD;
          rep (i, ch) t = t * (h + 1) % MOD;

          tmp = (tmp + t) % MOD;
        }
      }

      ans = (ans * tmp) % MOD;
    }

    return (ans + MOD) % MOD;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(0, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {50,50,50,50,524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {524,524}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 104060401; verify_case(1, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6,7,8,9,10,11}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {5,2,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,2,4,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 429287; verify_case(3, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {5,2,4,52,24,524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,4,20,24,500,504,520,524}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 97065655; verify_case(4, Arg2, howManyWays(Arg0, Arg1)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  AxonometricProjection ___test;
  ___test.run_test(-1);
}
// END CUT HERE
