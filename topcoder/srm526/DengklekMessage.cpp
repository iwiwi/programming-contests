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
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

const int M = 5000;

int nxt[510][60];
double inc[510];
double dp[2][510];

vector<int> init_kmp(const string &s) {
  int n = s.length();
  vector<int> next(n + 1);
  next[0] = -1;
  for (int i = 0, j = -1; i < n; next[++i] = ++j)
    while ((j >= 0) && (s[i] != s[j])) j = next[j];
  return next;
}

pair<int, int> advance_kmp(const string &s, const vector<int> &kmp, int p, const string &t) {
  int c = 0;
  rep (j, t.length()) {
    while (p > 0 && s[p] != t[j]) p = kmp[p];
    if (s[p] == t[j]) ++p;
    if (p == (int)s.length()) {
      p = kmp[p];
      ++c;
    }
  }
  return mp(p, c);
}

struct DengklekMessage {
  double theExpected(vector <string> P, vector <string> goodSubstring, long long K) {
    string S = accumulate(all(goodSubstring), string());
    int L = S.length(), N = P.size();

    vector<int> kmp = init_kmp(S);

    for (int p = 0; p < L; ++p) {
      inc[p] = 0;

      rep (i, N) {
        pair<int, int> q = advance_kmp(S, kmp, p, P[i]);
        nxt[p][i] = q.first;
        inc[p] += q.second / (double)N;
      }
    }

    memset(dp, 0, sizeof(dp));
    double *prv = dp[0], *crr = dp[1];
    prv[0] = 1.0;

    double ans = 0.0;

    int t;
    for (t = 0; t < min(K, (long long)M); ++t) {
      for (int p = 0; p <= L; ++p) crr[p] = 0;
      for (int p = 0; p <= L; ++p) ans += prv[p] * inc[p];

      for (int p = 0; p <= L; ++p) prv[p] /= N;
      for (int p = 0; p <= L; ++p) rep (i, N) crr[nxt[p][i]] += prv[p];

      swap(prv, crr);
    }

    double d = 0;
    for (int p = 0; p <= L; ++p) d += prv[p] * inc[p];
    ans += d * (K - t);

    return ans;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 10LL; double Arg3 = 9.0; verify_case(0, Arg3, theExpected(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; double Arg3 = 0.0; verify_case(1, Arg3, theExpected(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"0", "1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 3LL; double Arg3 = 0.5; verify_case(2, Arg3, theExpected(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"0", "10", "110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0", "1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 5LL; double Arg3 = 2.6666666666666665; verify_case(3, Arg3, theExpected(Arg0, Arg1, Arg2)); }
   void test_case_4() { string Arr0[] = {"0", "10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"000101000101010100"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 526LL; double Arg3 = 0.25146484375; verify_case(4, Arg3, theExpected(Arg0, Arg1, Arg2)); }

  /*
	void test_case_4() { string Arr0[] =
      {"0", "1"}
      ;

      vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] =

          {"01100100111110111001001111100010010000110110111001","01101110100001011001101001000001001111101011111100","10110111010100100100111011000001001010110011010111"}

      //{"11101101001100000100001111000100010100000000100100","10000001100101101011010000000101011011010000111100","10101101001100111111000001101101001001010110001011","00011110110011010100001110001011000011101100100111","11100001001110010110010000100110000001001100001100","00011000110001100010001101010110101111001100000000","01010011110110001011110100100100000010010011010101","00001000001110111011101101100010000100101101111100","00111101110010100111011111101110110101010011000101","00010111000001000001100101110110011001010001111110"}

                                                                               ;vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1000000000LL; double Arg3 = 0.25146484375; verify_case(4, Arg3, theExpected(Arg0, Arg1, Arg2)); }
  */

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  DengklekMessage ___test;
  ___test.run_test(-1);
}
// END CUT HERE
